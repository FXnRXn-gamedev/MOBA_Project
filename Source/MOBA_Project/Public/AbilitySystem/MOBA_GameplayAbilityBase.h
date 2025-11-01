// FXnRXn copyright

#pragma once

#include "CoreMinimal.h"
#include "Abilities/GameplayAbility.h"
#include "MOBA_GameplayAbilityBase.generated.h"

/**
 * 
 */
UCLASS()
class MOBA_PROJECT_API UMOBA_GameplayAbilityBase : public UGameplayAbility
{
	GENERATED_BODY()
	
	//------------------------------------------------------------------------------------------------------------------
protected:
	UPROPERTY(EditAnywhere, Category = "Moba|Ability")
	bool bDebug = false;
};
