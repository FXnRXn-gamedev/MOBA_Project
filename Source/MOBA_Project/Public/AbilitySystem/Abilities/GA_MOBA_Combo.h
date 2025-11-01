// FXnRXn copyright

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystem/MOBA_GameplayAbilityBase.h"
#include "GA_MOBA_Combo.generated.h"





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

	//------------------------------------------------------------------------------------------------------------------
private:
	UPROPERTY(EditDefaultsOnly, Category = "Moba|Animation")
	UAnimMontage* ComboMontage;

	UPROPERTY(EditDefaultsOnly, Category = "Moba|Animation")
	UAnimMontage* ComboMontage2;

	mutable bool bUseFirstMontage = true;
	UAnimMontage* GetRandomComboMontage() const;



	
};
