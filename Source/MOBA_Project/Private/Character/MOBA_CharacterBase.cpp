// FXnRXn copyright


#include "MOBA_Project/Public/Character/MOBA_CharacterBase.h"
#include "AbilitySystem/MOBA_AbilitySystemComponent.h"
#include "AbilitySystem/MOBA_AttributeSet.h"
#include "Components/WidgetComponent.h"
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
