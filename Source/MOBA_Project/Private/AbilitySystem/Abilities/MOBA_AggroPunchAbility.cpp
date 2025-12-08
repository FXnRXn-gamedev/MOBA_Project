// FXnRXn copyright


#include "AbilitySystem/Abilities/MOBA_AggroPunchAbility.h"

#include "MotionWarpingComponent.h"
#include "Abilities/Tasks/AbilityTask_PlayMontageAndWait.h"
#include "Abilities/Tasks/AbilityTask_WaitGameplayEvent.h"
#include "Abilities/Tasks/AbilityTask_WaitDelay.h"
#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"
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
	
	ACharacter* Character = Cast<ACharacter>(GetAvatarActorFromActorInfo());
	if (!IsValid(Character))
	{
		K2_EndAbility();
		return;
	}
	
	// Get Direction
	FVector Direction = Character->GetActorForwardVector();
	//if (Direction.IsNearlyZero()) Direction = Character->GetActorForwardVector();
	if (Direction.IsNearlyZero())
	{
		Direction = Character->GetControlRotation().Vector();
		Direction.Z = 0.0f; // Keep it horizontal
		Direction.Normalize();
	}
	Direction.Normalize();
	
	
	// Runs on: Server + Client (with prediction)
	if (HasAuthorityOrPredictionKey(ActorInfo, &ActivationInfo))
	{
		DoMotionWarpingDash(Character, Direction);
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

	if (HasAuthorityOrPredictionKey(ActorInfo, &ActivationInfo))
	{
		UAbilityTask_WaitGameplayEvent* WaitAggroPunchEventTask = UAbilityTask_WaitGameplayEvent::WaitGameplayEvent(this, GetAggroPunchLaunchTag());
		WaitAggroPunchEventTask->EventReceived.AddDynamic(this, &ThisClass::StartAggroLaunch);
		WaitAggroPunchEventTask->ReadyForActivation();
	}
	
	
	
	
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
// ACharacter* Character = Cast<ACharacter>(GetAvatarActorFromActorInfo());
// if (!IsValid(Character)) return;
// 	
// UCharacterMovementComponent* CharacterMovementComp = Character->GetCharacterMovement();
// if (!CharacterMovementComp) return;


void UMOBA_AggroPunchAbility::DoMotionWarpingDash(ACharacter* Character, const FVector& Direction)
{
	if (!AggroPunchMontage)
	{
		K2_EndAbility();
		return;
	}
	UCharacterMovementComponent* CharacterMovementComp = Character->GetCharacterMovement();
	if (!CharacterMovementComp) return;
	
	
	UMotionWarpingComponent* Warp = Character->FindComponentByClass<UMotionWarpingComponent>();
	if (Warp)
	{
		FVector Start = Character->GetActorLocation();
		FVector Target = Start + Direction * WarpDistance;

		Warp->AddOrUpdateWarpTargetFromLocation(AggroPunchWarpingSectionName, Target);
	}
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

