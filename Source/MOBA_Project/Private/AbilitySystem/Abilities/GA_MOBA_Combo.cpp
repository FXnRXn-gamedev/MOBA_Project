// FXnRXn copyright


#include "AbilitySystem/Abilities/GA_MOBA_Combo.h"
#include "Abilities/Tasks/AbilityTask_PlayMontageAndWait.h"
#include "AbilitySystem/MOBA_AbilitySystemStatics.h"


UGA_MOBA_Combo::UGA_MOBA_Combo()
{
	AbilityTags.AddTag(UMOBA_AbilitySystemStatics::GetBasicAttackAbilityTag());
	BlockAbilitiesWithTag.AddTag(UMOBA_AbilitySystemStatics::GetBasicAttackAbilityTag());
}

void UGA_MOBA_Combo::ActivateAbility(const FGameplayAbilitySpecHandle Handle,
                                     const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo,
                                     const FGameplayEventData* TriggerEventData)
{
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);
	if (!K2_CommitAbility())
	{
		K2_EndAbility();
		return;
	}
	
	UAnimMontage* SelectedComboMontage = GetRandomComboMontage();
	
	if ((ComboMontage != nullptr || ComboMontage2 != nullptr) && HasAuthorityOrPredictionKey(ActorInfo, &ActivationInfo))
	{
		UAbilityTask_PlayMontageAndWait* PlayComboMontageTask = UAbilityTask_PlayMontageAndWait::CreatePlayMontageAndWaitProxy(this, NAME_None, SelectedComboMontage);
		PlayComboMontageTask->OnBlendOut.AddDynamic(this, &UGA_MOBA_Combo::K2_EndAbility);
		PlayComboMontageTask->OnCancelled.AddDynamic(this, &UGA_MOBA_Combo::K2_EndAbility);
		PlayComboMontageTask->OnCompleted.AddDynamic(this, &UGA_MOBA_Combo::K2_EndAbility);
		PlayComboMontageTask->OnInterrupted.AddDynamic(this, &UGA_MOBA_Combo::K2_EndAbility);
		PlayComboMontageTask->ReadyForActivation();
	}
	
	// if (bDebug && GEngine)
	// {
	// 	GEngine->AddOnScreenDebugMessage(-1, 3.0f, FColor::Magenta, FString(TEXT("Debug: Casting GA Combo !!!")));
	// }
	
}

UAnimMontage* UGA_MOBA_Combo::GetRandomComboMontage() const
{
	UAnimMontage* SelectedMontage = nullptr;
	
	// Check if both montages are valid
	if (ComboMontage != nullptr && ComboMontage2 != nullptr)
	{
		// Flip-flop between the two montages
		if (bUseFirstMontage)
		{
			SelectedMontage = ComboMontage;
		}
		else
		{
			SelectedMontage = ComboMontage2;
		}
		
		// Toggle for next time
		bUseFirstMontage = !bUseFirstMontage;
	}
	// Fallback to available montage if only one is set
	else if (ComboMontage != nullptr)
	{
		SelectedMontage = ComboMontage;
	}
	else if (ComboMontage2 != nullptr)
	{
		SelectedMontage = ComboMontage2;
	}
	
	return SelectedMontage;


}
