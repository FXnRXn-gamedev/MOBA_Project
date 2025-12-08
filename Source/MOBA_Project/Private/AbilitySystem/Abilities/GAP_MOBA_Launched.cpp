// FXnRXn copyright


#include "AbilitySystem/Abilities/GAP_MOBA_Launched.h"




// =====================================================================================================================
// ---> CONSTRUCTOR & UNREAL CALLBACK <---
// =====================================================================================================================
UGAP_MOBA_Launched::UGAP_MOBA_Launched()
{
	NetExecutionPolicy = EGameplayAbilityNetExecutionPolicy::ServerOnly;
}




// =====================================================================================================================
// ---> GAS <---
// =====================================================================================================================


void UGAP_MOBA_Launched::ActivateAbility(const FGameplayAbilitySpecHandle Handle,
	const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo,
	const FGameplayEventData* TriggerEventData)
{
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);
	
	if (!K2_CommitAbility())
	{
		K2_EndAbility();
		return;
	}
	
	// Server only ability logic
	if (K2_HasAuthority())
	{
		PushSelf(TriggerEventData->TargetData.Get(0)->GetHitResult()->ImpactNormal);
		K2_EndAbility();
	}
}
