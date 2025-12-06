// FXnRXn copyright


#include "AbilitySystem/Abilities/MOBA_AggroPunchAbility.h"
#include "Abilities/Tasks/AbilityTask_PlayMontageAndWait.h"
#include "Abilities/Tasks/AbilityTask_WaitGameplayEvent.h"
#include "GameFramework/Character.h"
#include "Utility/MOBA_DebugHelper.h"


// =====================================================================================================================
// ---> CONSTRUCTOR & UNREAL CALLBACK <---
// =====================================================================================================================

UMOBA_AggroPunchAbility::UMOBA_AggroPunchAbility()
{
	InstancingPolicy = EGameplayAbilityInstancingPolicy::InstancedPerActor;
	NetExecutionPolicy = EGameplayAbilityNetExecutionPolicy::LocalPredicted;
}






// =====================================================================================================================
// ---> GAS <---
// =====================================================================================================================

void UMOBA_AggroPunchAbility::ActivateAbility(const FGameplayAbilitySpecHandle Handle,
                                              const FGameplayAbilityActorInfo* ActorInfo, 
                                              const FGameplayAbilityActivationInfo ActivationInfo,
                                              const FGameplayEventData* TriggerEventData)
{
	if (!K2_CommitAbility())
	{
		K2_EndAbility();
		return;
	}
	
	// Runs on: Server + Client (with prediction)
	if (HasAuthorityOrPredictionKey(ActorInfo, &ActivationInfo))
	{
		if (!bUseRootMotion) PerformForwardDash();
	}
	
	// Runs on: Server ONLY
	if (K2_HasAuthority())
	{
		
	}
	
	if (AggroPunchMontage != nullptr && HasAuthorityOrPredictionKey(ActorInfo, &ActivationInfo))
	{
		UAbilityTask_PlayMontageAndWait* PlayAggroPunchMontageTask = UAbilityTask_PlayMontageAndWait::CreatePlayMontageAndWaitProxy(this, NAME_None, AggroPunchMontage);
		PlayAggroPunchMontageTask->OnBlendOut.AddDynamic(this, &ThisClass::K2_EndAbility);
		PlayAggroPunchMontageTask->OnCancelled.AddDynamic(this, &ThisClass::K2_EndAbility);
		PlayAggroPunchMontageTask->OnCompleted.AddDynamic(this, &ThisClass::K2_EndAbility);
		PlayAggroPunchMontageTask->OnInterrupted.AddDynamic(this, &ThisClass::K2_EndAbility);
		PlayAggroPunchMontageTask->ReadyForActivation();
	}
	
	
	
	UAbilityTask_WaitGameplayEvent* WaitAggroPunchEventTask = UAbilityTask_WaitGameplayEvent::WaitGameplayEvent(this, GetAggroPunchLaunchTag());
	WaitAggroPunchEventTask->EventReceived.AddDynamic(this, &ThisClass::StartAggroLaunch);
	WaitAggroPunchEventTask->ReadyForActivation();
}

void UMOBA_AggroPunchAbility::EndAbility(const FGameplayAbilitySpecHandle Handle,
										const FGameplayAbilityActorInfo* ActorInfo, 
										const FGameplayAbilityActivationInfo ActivationInfo,
										bool bReplicateEndAbility, 
										bool bWasCancelled)
{
	Super::EndAbility(Handle, ActorInfo, ActivationInfo, bReplicateEndAbility, bWasCancelled);
}






// =====================================================================================================================
// ---> TAG <---
// =====================================================================================================================

FGameplayTag UMOBA_AggroPunchAbility::GetAggroPunchLaunchTag()
{
	return FGameplayTag::RequestGameplayTag("MOBA_Tags.MOBA_Abilities.AggroPunch.Launch");
}










// =====================================================================================================================
// ---> ABILITY FUNCTION<---
// =====================================================================================================================


void UMOBA_AggroPunchAbility::PerformForwardDash()
{
	ACharacter* Character = Cast<ACharacter>(GetAvatarActorFromActorInfo());
	if (!IsValid(Character)) return;
	
	UCharacterMovementComponent* CharacterMovementComp = Character->GetCharacterMovement();
	if (!CharacterMovementComp) return;
	
	// Get Forward Direction
	FVector ForwardDirection = Character->GetActorForwardVector();
	ForwardDirection.Z = 0.0f;
	ForwardDirection.Normalize();
	
	// Calculate launch velocity
	float LaunchSpeed = DashDistance / DashDuration;
	FVector LaunchVelocity = ForwardDirection * LaunchSpeed;
	
	// Launch character forward
	// bXYOverride = true: Override horizontal velocity
	// bZOverride = false: Preserve vertical velocity (gravity)
	Character->LaunchCharacter(LaunchVelocity, true, false);
}

void UMOBA_AggroPunchAbility::StartAggroLaunch(FGameplayEventData EventData)
{
	TArray<FHitResult> TargetHitResults = GetHitResultFromSweepLocationTargetData(EventData.TargetData, TargetSweepSphereHitRadius, ETeamAttitude::Hostile, bDebugDamageSweep);

	if (K2_HasAuthority())
	{
		for (FHitResult& HitResult : TargetHitResults)
		{
			FString Msg = FString::Printf(TEXT("Aggro Punch Hit : %s"), *HitResult.GetActor()->GetName());
			MOBA_DebugHelper::DebugPrint(Msg);
		}
	}
}

