// FXnRXn copyright

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystem/MOBA_GameplayAbilityBase.h"
#include "MOBA_AggroPunchAbility.generated.h"




UCLASS()
class MOBA_PROJECT_API UMOBA_AggroPunchAbility : public UMOBA_GameplayAbilityBase
{
	GENERATED_BODY()
	
	//------------------------------------------------------------------------------------------------------------------
public:
	UMOBA_AggroPunchAbility();
	
	
	virtual void ActivateAbility(
		const FGameplayAbilitySpecHandle Handle, 
		const FGameplayAbilityActorInfo* ActorInfo, 
		const FGameplayAbilityActivationInfo ActivationInfo, 
		const FGameplayEventData* TriggerEventData) override;
	
	virtual void EndAbility(
		const FGameplayAbilitySpecHandle Handle, 
		const FGameplayAbilityActorInfo* ActorInfo, 
		const FGameplayAbilityActivationInfo ActivationInfo, 
		bool bReplicateEndAbility, 
		bool bWasCancelled) override;
	
	//------------------------------------------------------------------------------------------------------------------
private:
	
	static FGameplayTag GetAggroPunchLaunchTag();
	
	
	//--------------------------------------------------
	// HIT
	//--------------------------------------------------
	UPROPERTY(EditDefaultsOnly, Category = "Moba|Targeting")
	float TargetSweepSphereHitRadius = 80.f;
	
	
	
	
	
	
	//--------------------------------------------------
	// DASH MOVE
	//--------------------------------------------------
	
	UPROPERTY(EditDefaultsOnly, Category = "Moba|Dash")
	float WarpDistance = 600.f;
	
	
	void DoMotionWarpingDash(ACharacter* Character, const FVector& Direction);
	
	
	UFUNCTION()
	void StartAggroLaunch(FGameplayEventData EventData);
	
	//--------------------------------------------------
	// MONTAGE
	//--------------------------------------------------
	UPROPERTY(EditDefaultsOnly, Category = "Moba|Animation")
	FName AggroPunchWarpingSectionName = "AggroDash";
	
	UPROPERTY(EditDefaultsOnly, Category = "Moba|Animation")
	UAnimMontage* AggroPunchMontage;
	
	
};
