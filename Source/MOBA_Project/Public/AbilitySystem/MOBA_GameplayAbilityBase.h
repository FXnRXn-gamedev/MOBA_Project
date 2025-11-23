// FXnRXn copyright

#pragma once

#include "CoreMinimal.h"
#include "Abilities/GameplayAbility.h"
#include "GenericTeamAgentInterface.h"
#include "MOBA_GameplayAbilityBase.generated.h"

class UAnimInstanceBase;


UCLASS()
class MOBA_PROJECT_API UMOBA_GameplayAbilityBase : public UGameplayAbility
{
	GENERATED_BODY()
	
	//------------------------------------------------------------------------------------------------------------------
protected:
	
	UAnimInstance* GetOwnerAnimInstance() const;

	TArray<FHitResult> GetHitResultFromSweepLocationTargetData(
		const FGameplayAbilityTargetDataHandle& TargetDataHandle,
		float SphereSweepRadius = 30.0f,
		ETeamAttitude::Type TargetTeam = ETeamAttitude::Hostile,
		bool bIgnoreSelf = true) const;



	

#pragma region Debug
	
	UPROPERTY(EditAnywhere, Category = "Moba|Debug")
	bool bDebug = false;

	UPROPERTY(EditAnywhere, Category = "Moba|Debug")
	bool bDebugDamageSweep = false;

#pragma endregion 
};
