// FXnRXn copyright


#include "AbilitySystem/MOBA_AbilitySystemComponent.h"

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
