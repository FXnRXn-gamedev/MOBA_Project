// FXnRXn copyright


#include "AbilitySystem/Abilities/GA_MOBA_Combo.h"
#include "Abilities/Tasks/AbilityTask_PlayMontageAndWait.h"
#include "Abilities/Tasks/AbilityTask_WaitGameplayEvent.h"
#include "Abilities/Tasks/AbilityTask_WaitInputPress.h"
#include "AbilitySystem/MOBA_AbilitySystemStatics.h"
#include "GameplayTag/MOBA_GameplayTags.h"
#include "GameplayTagsManager.h"


UGA_MOBA_Combo::UGA_MOBA_Combo()
{
	const FGameplayTag BasicAttackTag = UMOBA_AbilitySystemStatics::GetBasicAttackAbilityTag();
	
	FGameplayTagContainer NewAbilityTags;
	NewAbilityTags.AddTag(BasicAttackTag);
	SetAssetTags(NewAbilityTags);

	BlockAbilitiesWithTag.AddTag(BasicAttackTag);
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
	
	// Initialize the input task pointer
	CurrentInputPressTask = nullptr;

	
	if (AttackComboMontage != nullptr && HasAuthorityOrPredictionKey(ActorInfo, &ActivationInfo))
	{
		UAbilityTask_PlayMontageAndWait* PlayComboMontageTask = UAbilityTask_PlayMontageAndWait::CreatePlayMontageAndWaitProxy(this, NAME_None, AttackComboMontage);
		PlayComboMontageTask->OnBlendOut.AddDynamic(this, &UGA_MOBA_Combo::K2_EndAbility);
		PlayComboMontageTask->OnCancelled.AddDynamic(this, &UGA_MOBA_Combo::K2_EndAbility);
		PlayComboMontageTask->OnCompleted.AddDynamic(this, &UGA_MOBA_Combo::K2_EndAbility);
		PlayComboMontageTask->OnInterrupted.AddDynamic(this, &UGA_MOBA_Combo::K2_EndAbility);
		PlayComboMontageTask->ReadyForActivation();

		// Listen for next combo change
		UAbilityTask_WaitGameplayEvent* WaitComboChangeEventTask = UAbilityTask_WaitGameplayEvent::WaitGameplayEvent(this,
			GetComboChangeEventTag(), nullptr, false, false);
		WaitComboChangeEventTask->EventReceived.AddDynamic(this, &UGA_MOBA_Combo::ComboChangeEventRecieved);
		WaitComboChangeEventTask->ReadyForActivation();

		// Listen for combo change END events
		UAbilityTask_WaitGameplayEvent* WaitComboChangeEndEventTask = UAbilityTask_WaitGameplayEvent::WaitGameplayEvent(this,
			GetComboChangeEndEventTag(), nullptr, false, false);
		WaitComboChangeEndEventTask->EventReceived.AddDynamic(this, &UGA_MOBA_Combo::ComboChangeEventRecieved);
		WaitComboChangeEndEventTask->ReadyForActivation();
	}
	
	SetupWaitComboInputPress();
}

// Override EndAbility to clean up tasks

void UGA_MOBA_Combo::EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo,
	const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled)
{
	// Clean up the input task when ability ends
	if (CurrentInputPressTask && IsValid(CurrentInputPressTask))
	{
		CurrentInputPressTask->EndTask();
		CurrentInputPressTask = nullptr;
	}
	
	Super::EndAbility(Handle, ActorInfo, ActivationInfo, bReplicateEndAbility, bWasCancelled);
}


//----------------------------------------------------------------------------------------------------------------------
//--> COMBO EVENT TAG


FGameplayTag UGA_MOBA_Combo::GetComboChangeEventTag()
{
	return FGameplayTag::RequestGameplayTag("MOBA_Tags.MOBA_Events.PlayerEvent");
}

FGameplayTag UGA_MOBA_Combo::GetComboChangeEndEventTag()
{
	return FGameplayTag::RequestGameplayTag("MOBA_Tags.MOBA_Events.PlayerEvent.ComboAttackEnd");
}

void UGA_MOBA_Combo::ComboChangeEventRecieved(FGameplayEventData Data)
{
	FGameplayTag EventTag = Data.EventTag;
	if (EventTag == GetComboChangeEndEventTag())
	{
		NextComboName = NAME_None;
		return;
	}
	TArray<FName> TagNames;
	UGameplayTagsManager& GameplayTagsManager = UGameplayTagsManager::Get();
	GameplayTagsManager.SplitGameplayTagFName(EventTag, TagNames);
	NextComboName = TagNames.Last();
}


void UGA_MOBA_Combo::TryCommitForNextCombo()
{
	if (NextComboName == NAME_None) return;

	UAnimInstance* OwnerAnimInstance = GetOwnerAnimInstance();
	if (!OwnerAnimInstance) return;

	OwnerAnimInstance->Montage_SetNextSection(OwnerAnimInstance->Montage_GetCurrentSection(AttackComboMontage), NextComboName, AttackComboMontage);
}

//----------------------------------------------------------------------------------------------------------------------
//--> COMBO EVENT INPUT PRESS

void UGA_MOBA_Combo::SetupWaitComboInputPress()
{
	// Clean up existing input task before creating a new one
	if (CurrentInputPressTask && IsValid(CurrentInputPressTask))
	{
		CurrentInputPressTask->EndTask();
	}

	CurrentInputPressTask = UAbilityTask_WaitInputPress::WaitInputPress(this);
	if (!CurrentInputPressTask) return;
	
	CurrentInputPressTask->OnPress.AddDynamic(this, &UGA_MOBA_Combo::HandleComboInputPressRecieved);
	CurrentInputPressTask->ReadyForActivation();
}

void UGA_MOBA_Combo::HandleComboInputPressRecieved(float TimeWaited)
{
	SetupWaitComboInputPress();
	TryCommitForNextCombo();
}
