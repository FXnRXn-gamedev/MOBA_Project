// FXnRXn copyright

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystem/MOBA_GameplayAbilityBase.h"
#include "GAP_MOBA_Launched.generated.h"

/**
 * 
 */
UCLASS()
class MOBA_PROJECT_API UGAP_MOBA_Launched : public UMOBA_GameplayAbilityBase
{
	GENERATED_BODY()
	//------------------------------------------------------------------------------------------------------------------
public:
	UGAP_MOBA_Launched();
	virtual void ActivateAbility(const FGameplayAbilitySpecHandle Handle, 
		const FGameplayAbilityActorInfo* ActorInfo, 
		const FGameplayAbilityActivationInfo ActivationInfo, 
		const FGameplayEventData* TriggerEventData) override;
};
