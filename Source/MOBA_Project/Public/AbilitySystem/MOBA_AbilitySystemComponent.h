// FXnRXn copyright

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemComponent.h"
#include "MOBA_AbilitySystemComponent.generated.h"






UCLASS()
class MOBA_PROJECT_API UMOBA_AbilitySystemComponent : public UAbilitySystemComponent
{
	GENERATED_BODY()

	//------------------------------------------------------------------------------------------------------------------
public:
	void ApplyInitialEffects();


	//------------------------------------------------------------------------------------------------------------------
private:
	UPROPERTY(EditDefaultsOnly, Category = "GameplayEffects")
	TArray<TSubclassOf<UGameplayEffect>> InitialEffects;
};
