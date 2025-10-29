// FXnRXn copyright


#include "MOBA_Project/Public/Character/MOBA_CharacterBase.h"
#include "AbilitySystem/MOBA_AbilitySystemComponent.h"
#include "AbilitySystem/MOBA_AttributeSet.h"





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



// --> GAMEPLAY ABILITY <--
//----------------------------------------

UAbilitySystemComponent* AMOBA_CharacterBase::GetAbilitySystemComponent() const
{
	return AbilitySystemComp;
}