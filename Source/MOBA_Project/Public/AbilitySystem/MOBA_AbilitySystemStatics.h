// FXnRXn copyright

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "MOBA_AbilitySystemStatics.generated.h"


UCLASS()
class MOBA_PROJECT_API UMOBA_AbilitySystemStatics : public UBlueprintFunctionLibrary

{
	GENERATED_BODY()
	//------------------------------------------------------------------------------------------------------------------
public:
	UFUNCTION(BlueprintPure, Category = "Moba|Ability Tag")
	static FGameplayTag GetBasicAttackAbilityTag();

	static FGameplayTag GetDeadStatTag();
};

