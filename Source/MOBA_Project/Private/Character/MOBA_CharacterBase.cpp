// FXnRXn copyright


#include "MOBA_Project/Public/Character/MOBA_CharacterBase.h"
#include "AbilitySystem/MOBA_AbilitySystemComponent.h"
#include "AbilitySystem/MOBA_AbilitySystemStatics.h"
#include "AbilitySystem/MOBA_AttributeSet.h"
#include "Components/CapsuleComponent.h"
#include "Components/WidgetComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Widgets/MOBA_OverHeadStats.h"


// --> CONSTRUCTOR <--
//----------------------------------------
AMOBA_CharacterBase::AMOBA_CharacterBase()
{
	PrimaryActorTick.bCanEverTick = false;

	GetMesh()->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	// Create Ability System Component
	AbilitySystemComp = CreateDefaultSubobject<UMOBA_AbilitySystemComponent>(TEXT("AbilitySystemComponent"));
	AbilitySystemComp->SetIsReplicated(true);
	AbilitySystemComp->SetReplicationMode(EGameplayEffectReplicationMode::Mixed);

	// Create Attribute Set
	AttributeSet = CreateDefaultSubobject<UMOBA_AttributeSet>(TEXT("AttributeSet"));

	// Create HeadOver Widget
	OverHeadWidgetComponent = CreateDefaultSubobject<UWidgetComponent>(TEXT("OverHeadWidgetComponent"));
	OverHeadWidgetComponent->SetupAttachment(GetRootComponent());

	BindGASChangeDelegates();
	
}

void AMOBA_CharacterBase::BeginPlay()
{
	Super::BeginPlay();

	ConfigureOverHeadWidget();
}


// --> Server-Client Chain <--
//----------------------------------------


void AMOBA_CharacterBase::ServerSideInit()
{
	// Init Ability for this (so Player and enemy both have ability component)
	AbilitySystemComp->InitAbilityActorInfo(this, this);
	// Init Ability Effect
	AbilitySystemComp->ApplyInitialEffects();
	// Init Ability
	AbilitySystemComp->GiveInitialAbilities();
}

void AMOBA_CharacterBase::ClientSideInit()
{
	// Init Ability Component
	AbilitySystemComp->InitAbilityActorInfo(this, this);
}

void AMOBA_CharacterBase::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);
	if (NewController && NewController->IsPlayerController())
	{
		ServerSideInit();
	}
}

bool AMOBA_CharacterBase::IsLocallyControlledByPlayer() const
{
	return GetController() && GetController()->IsLocalPlayerController();
}


// --> GAMEPLAY ABILITY <--
//----------------------------------------

UAbilitySystemComponent* AMOBA_CharacterBase::GetAbilitySystemComponent() const
{
	return AbilitySystemComp;
}

void AMOBA_CharacterBase::BindGASChangeDelegates()
{
	if (IsValid(AbilitySystemComp))
	{
		AbilitySystemComp->RegisterGameplayTagEvent(UMOBA_AbilitySystemStatics::GetDeadStatTag()). AddUObject(this, &AMOBA_CharacterBase::OnDeathTagUpdated);
	}
}

void AMOBA_CharacterBase::OnDeathTagUpdated(const FGameplayTag Tag, int32 NewCount)
{
	if (NewCount != 0)
	{
		StartDeathSequence();
	}else
	{
		Respawn();
	}
}


// --> WIDGET <--
//----------------------------------------


void AMOBA_CharacterBase::ConfigureOverHeadWidget()
{
	if (IsLocallyControlledByPlayer())
	{
		OverHeadWidgetComponent->SetHiddenInGame(true);
		return;
	}
	if (!IsValid(OverHeadWidgetComponent)) return;
	if (!IsValid(GetAbilitySystemComponent())) return;

	
	

	UMOBA_OverHeadStats* OverHeadStatsWidget = Cast<UMOBA_OverHeadStats>(OverHeadWidgetComponent->GetUserWidgetObject());
	if (OverHeadStatsWidget)
	{
		OverHeadStatsWidget->ConfigureWithASC(GetAbilitySystemComponent());
		OverHeadWidgetComponent->SetHiddenInGame(false);
		GetWorldTimerManager().ClearTimer(OverHeadVisibilityWidgetTimerHandle);
		GetWorldTimerManager().SetTimer(OverHeadVisibilityWidgetTimerHandle, this, &AMOBA_CharacterBase::UpdateOverHeadVisibilityWidget, OverHeadWidgetVisibilityTimerUpdate, true);
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("OverHeadWidgetComponent is not set!"));
	}
}

void AMOBA_CharacterBase::UpdateOverHeadVisibilityWidget()
{
	APawn* LocalPlayerPawn = UGameplayStatics::GetPlayerPawn(this, 0);
	if (!IsValid(LocalPlayerPawn)) return;

	float DistanceSquared = FVector::DistSquared(GetActorLocation(), LocalPlayerPawn->GetActorLocation());
	
	OverHeadWidgetComponent->SetHiddenInGame(DistanceSquared > OverHeadWidgetVisibilitySquaredRange);
}

void AMOBA_CharacterBase::SetStatWidgetEnabled(bool bIsEnabled)
{
	GetWorldTimerManager().ClearTimer(OverHeadVisibilityWidgetTimerHandle);
	if (bIsEnabled)
	{
		ConfigureOverHeadWidget();
	}else
	{
		OverHeadWidgetComponent->SetHiddenInGame(true);
	}
}


// --> Death & Respawn <--
//----------------------------------------


void AMOBA_CharacterBase::StartDeathSequence()
{
	OnDead();
	PlayDeathMontage();
	SetStatWidgetEnabled(false);
	GetCharacterMovement()->SetMovementMode(EMovementMode::MOVE_None);
	GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
}

void AMOBA_CharacterBase::Respawn()
{
	OnRespawn();
}


void AMOBA_CharacterBase::PlayDeathMontage()
{
	if (!DeathMontage)
	{
		UE_LOG(LogTemp, Warning, TEXT("DeathMontage is not set!"));
		return;
	}
	PlayAnimMontage(DeathMontage);
}

void AMOBA_CharacterBase::OnDead()
{
}

void AMOBA_CharacterBase::OnRespawn()
{
}


