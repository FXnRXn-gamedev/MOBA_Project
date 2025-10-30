// FXnRXn copyright

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "GameplayEffectTypes.h"
#include "MOBA_OverHeadStats.generated.h"

struct FOnAttributeChangeData;
class UAbilitySystemComponent;
class UMOBA_AttributeValueGauge;



UCLASS()
class MOBA_PROJECT_API UMOBA_OverHeadStats : public UUserWidget
{
	GENERATED_BODY()

	//------------------------------------------------------------------------------------------------------------------
public:
	void ConfigureWithASC(UAbilitySystemComponent* AbilitySystemComponent);
	void InitializeStatBar();

	//------------------------------------------------------------------------------------------------------------------
private:

	UPROPERTY(meta=(BindWidget))
	UMOBA_AttributeValueGauge* HealthBar;

	UPROPERTY(meta=(BindWidget))
	UMOBA_AttributeValueGauge* ManaBar;

	UPROPERTY()
	UAbilitySystemComponent* OwnerAbilitySystemComp;


	void OnHealthChanged(const FOnAttributeChangeData& Data);
	void OnManaChanged(const FOnAttributeChangeData& Data);
	
	void InitHealthBar();
	void InitManaBar();
	
};
