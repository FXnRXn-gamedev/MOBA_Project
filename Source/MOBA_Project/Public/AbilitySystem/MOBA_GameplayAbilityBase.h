// FXnRXn copyright

#pragma once

#include "CoreMinimal.h"
#include "Abilities/GameplayAbility.h"
#include "GenericTeamAgentInterface.h"
#include "GameFramework/Character.h"
#include "MOBA_GameplayAbilityBase.generated.h"

class UAnimInstanceBase;


UCLASS()
class MOBA_PROJECT_API UMOBA_GameplayAbilityBase : public UGameplayAbility
{
	GENERATED_BODY()
	
	//------------------------------------------------------------------------------------------------------------------
protected:
	
	// ANIOMATION
	UAnimInstance* GetOwnerAnimInstance() const;
	
	
	// HIT DETECTION
	TArray<FHitResult> GetHitResultFromSweepLocationTargetData(
		const FGameplayAbilityTargetDataHandle& TargetDataHandle,
		float SphereSweepRadius = 30.0f,
		ETeamAttitude::Type TargetTeam = ETeamAttitude::Hostile,
		bool bIgnoreSelf = true) const;
	
	
	// PUSH
	UPROPERTY(EditAnywhere, Category = "Moba|Settings")
	bool bIgnorePushSelf = true;
	
	void PushSelf(const FVector& PushDirection, float Strength = 500.0f) const;
	
	ACharacter* GetOwningAvatarCharacter() const
	{
		if (!AvatarCharacterCache)
		{
			AvatarCharacterCache = Cast<ACharacter>(GetAvatarActorFromActorInfo());
		}
		return AvatarCharacterCache;
	}
	
private:
	UPROPERTY()
	mutable ACharacter* AvatarCharacterCache;
	
	// =================================================================================================================
	// ---> DEBUG <---
	// =================================================================================================================
protected:
#pragma region Debug
	
	UPROPERTY(EditAnywhere, Category = "Moba|Debug")
	bool bDebug = false;

	UPROPERTY(EditAnywhere, Category = "Moba|Debug")
	bool bDebugDamageSweep = false;
	

#pragma endregion 
};
