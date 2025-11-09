// FXnRXn copyright


#include "AbilitySystem/MOBA_AbilitySystemComponent.h"
#include "AbilitySystem/MOBA_AttributeSet.h"

UMOBA_AbilitySystemComponent::UMOBA_AbilitySystemComponent()
{
	GetGameplayAttributeValueChangeDelegate(UMOBA_AttributeSet::GetHealthAttribute()).AddUObject(this, &UMOBA_AbilitySystemComponent::OnHealthUpdated);
}

void UMOBA_AbilitySystemComponent::ApplyInitialEffects()
{
	if (!GetOwner() || !GetOwner()->HasAuthority()) return;

	
	// Init Effect only applicable in server side
	for (const TSubclassOf<UGameplayEffect>& EffectClass : InitialEffects)
	{
		checkf(IsValid(EffectClass), TEXT("InitializeEfffect is not set!"));

		FGameplayEffectSpecHandle EffectSpecHandle =MakeOutgoingSpec(EffectClass, 1, MakeEffectContext());
		ApplyGameplayEffectSpecToSelf(*EffectSpecHandle.Data.Get());
	}
}

void UMOBA_AbilitySystemComponent::GiveInitialAbilities()
{
	if (!GetOwner() || !GetOwner()->HasAuthority()) return;

	
	// Init Ability only applicable in server side

	
	for (const TPair<EMOBA_AbilityInputID, TSubclassOf<UGameplayAbility>>& AbilityPairClass : Abilities)
	{
		if(!IsValid(AbilityPairClass.Value))
		{
			UE_LOG(LogTemp, Warning, TEXT("Abilities Not set in AbilitySystemComponent!!"));
			return;
		}
	
		GiveAbility(FGameplayAbilitySpec(AbilityPairClass.Value, 0, (int32)AbilityPairClass.Key, nullptr));
	}

	for (const TPair<EMOBA_AbilityInputID, TSubclassOf<UGameplayAbility>>& BasicAbilityPairClass : BasicAbilities)
	{
		if(!IsValid(BasicAbilityPairClass.Value))
		{
			UE_LOG(LogTemp, Warning, TEXT("Basic Abilities Not set in AbilitySystemComponent!!"));
			return;
		}
	
		GiveAbility(FGameplayAbilitySpec(BasicAbilityPairClass.Value, 1, (int32)BasicAbilityPairClass.Key, nullptr));
	}
}

void UMOBA_AbilitySystemComponent::OnHealthUpdated(const FOnAttributeChangeData& ChangeData)
{
	if (!GetOwner()) return;
	if (ChangeData.NewValue <= 0.0f && GetOwner()->HasAuthority() && DeathEffect)
	{
		FGameplayEffectSpecHandle EffectSpecHandle =MakeOutgoingSpec(DeathEffect, 1, MakeEffectContext());
		ApplyGameplayEffectSpecToSelf(*EffectSpecHandle.Data.Get());
	}
}
