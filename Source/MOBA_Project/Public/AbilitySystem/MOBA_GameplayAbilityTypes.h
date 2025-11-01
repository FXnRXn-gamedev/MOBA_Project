// FXnRXn copyright

#pragma once

#include "CoreMinimal.h"
#include "MOBA_GameplayAbilityTypes.generated.h"


UENUM(BlueprintType)
enum class EMOBA_AbilityInputID: uint8
{
	NONE				UMETA(DisplayName = "None"),
	BasicAttackOne		UMETA(DisplayName = "BasicAttackOne"),
	AbilityOne			UMETA(DisplayName = "AbilityOne"),
	AbilityTwo			UMETA(DisplayName = "AbilityTwo"),
	AbilityThree		UMETA(DisplayName = "AbilityThree"),
	AbilityFour			UMETA(DisplayName = "AbilityFour"),
	AbilityFive			UMETA(DisplayName = "AbilityFive"),
	AbilitySix			UMETA(DisplayName = "AbilitySix"),
	Confirmed			UMETA(DisplayName = "Confirmed"),
	Cancelled			UMETA(DisplayName = "Cancelled")
};
