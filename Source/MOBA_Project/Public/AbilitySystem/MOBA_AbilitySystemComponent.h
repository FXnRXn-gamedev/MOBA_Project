// FXnRXn copyright

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemComponent.h"
#include "MOBA_GameplayAbilityTypes.h"
#include "MOBA_AbilitySystemComponent.generated.h"






UCLASS()
class MOBA_PROJECT_API UMOBA_AbilitySystemComponent : public UAbilitySystemComponent
{
	GENERATED_BODY()

	//------------------------------------------------------------------------------------------------------------------
public:
	void ApplyInitialEffects(); //Init Attribute stat, full stat
	void GiveInitialAbilities();


	//------------------------------------------------------------------------------------------------------------------
private:
	UPROPERTY(EditDefaultsOnly, Category = "Moba|GameplayEffects")
	TArray<TSubclassOf<UGameplayEffect>> InitialEffects;

	UPROPERTY(EditDefaultsOnly, Category = "Moba|Ability")
	TMap<EMOBA_AbilityInputID ,TSubclassOf<UGameplayAbility>> Abilities;

	UPROPERTY(EditDefaultsOnly, Category = "Moba|Ability")
	TMap<EMOBA_AbilityInputID ,TSubclassOf<UGameplayAbility>> BasicAbilities;
};
