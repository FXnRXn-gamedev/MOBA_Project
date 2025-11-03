// FXnRXn copyright

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystem/MOBA_GameplayAbilityBase.h"
#include "GA_MOBA_Combo.generated.h"


class UAbilityTask_WaitInputPress;


UCLASS()
class MOBA_PROJECT_API UGA_MOBA_Combo : public UMOBA_GameplayAbilityBase
{
	GENERATED_BODY()

	//------------------------------------------------------------------------------------------------------------------
public:
	UGA_MOBA_Combo();

	
	virtual void ActivateAbility(
		const FGameplayAbilitySpecHandle Handle,
		const FGameplayAbilityActorInfo* ActorInfo,
		const FGameplayAbilityActivationInfo ActivationInfo,
		const FGameplayEventData* TriggerEventData) override;

	virtual void EndAbility(const FGameplayAbilitySpecHandle Handle,
		const FGameplayAbilityActorInfo* ActorInfo,
		const FGameplayAbilityActivationInfo ActivationInfo,
		bool bReplicateEndAbility, bool bWasCancelled) override;

	static FGameplayTag GetComboChangeEventTag();
	static FGameplayTag GetComboChangeEndEventTag();
	static FGameplayTag GetComboTargetDamageEventTag();

	//------------------------------------------------------------------------------------------------------------------
private:

#pragma region Handle Combo Montage
	void TryCommitForNextCombo();
	void SetupWaitComboInputPress();
	FName NextComboName;

	
	UPROPERTY(EditDefaultsOnly, Category = "Moba|Animation")
	UAnimMontage* AttackComboMontage;
	UPROPERTY()
	TObjectPtr<UAbilityTask_WaitInputPress> CurrentInputPressTask;
	
	
	UFUNCTION()
	void ComboChangeEventRecieved(FGameplayEventData Data);
	UFUNCTION()
	void HandleComboInputPressRecieved(float TimeWaited);
	
#pragma endregion

#pragma region Handle Combo Damage
	

	UFUNCTION()
	void DoComboDamage(FGameplayEventData Data);

#pragma endregion

#pragma region GameplayEffects
	UPROPERTY(EditDefaultsOnly, Category = "Moba|GameplayEffect")
	TSubclassOf<UGameplayEffect> DefaultComboDamageEffect;
	
	UPROPERTY(EditDefaultsOnly, Category = "Moba|GameplayEffect")
	TMap<FName, TSubclassOf<UGameplayEffect>> ComboDamageEffectsMap;

	TSubclassOf<UGameplayEffect> GetDamageEffectForCurrentCombo() const;

#pragma endregion 
	
};
