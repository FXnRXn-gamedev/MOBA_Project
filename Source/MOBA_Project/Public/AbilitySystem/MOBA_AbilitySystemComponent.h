// FXnRXn copyright

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemComponent.h"
#include "GameplayEffectTypes.h"
#include "MOBA_GameplayAbilityTypes.h"
#include "MOBA_AbilitySystemComponent.generated.h"






UCLASS()
class MOBA_PROJECT_API UMOBA_AbilitySystemComponent : public UAbilitySystemComponent
{
	GENERATED_BODY()

	//------------------------------------------------------------------------------------------------------------------
public:
	UMOBA_AbilitySystemComponent();
	void ApplyInitialEffects(); //Init Attribute stat, full stat
	void GiveInitialAbilities();
	void ApplyFullStatEffect();

	//------------------------------------------------------------------------------------------------------------------
private:
	void OnHealthUpdated(const FOnAttributeChangeData& ChangeData);
	void AuthApplyGameplayEffect(TSubclassOf<UGameplayEffect>& GameplayEffect, int Level = 1);


	UPROPERTY(EditDefaultsOnly, Category = "Moba|GameplayEffects")
	TSubclassOf<UGameplayEffect> FullStatEffect;

	UPROPERTY(EditDefaultsOnly, Category = "Moba|GameplayEffects")
	TSubclassOf<UGameplayEffect> DeathEffect;
	
	UPROPERTY(EditDefaultsOnly, Category = "Moba|GameplayEffects")
	TArray<TSubclassOf<UGameplayEffect>> InitialEffects;

	UPROPERTY(EditDefaultsOnly, Category = "Moba|Ability")
	TMap<EMOBA_AbilityInputID ,TSubclassOf<UGameplayAbility>> Abilities;

	UPROPERTY(EditDefaultsOnly, Category = "Moba|Ability")
	TMap<EMOBA_AbilityInputID ,TSubclassOf<UGameplayAbility>> BasicAbilities;
};
