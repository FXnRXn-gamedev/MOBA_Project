// FXnRXn copyright

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "AttributeSet.h"
#include "GameplayEffectTypes.h"
#include "MOBA_GameplayWidget.generated.h"

struct FOnAttributeChangeData;
class UMOBA_AttributeValueGauge;
class UAbilitySystemComponent;


UCLASS()
class MOBA_PROJECT_API UMOBA_GameplayWidget : public UUserWidget
{
	GENERATED_BODY()

	//------------------------------------------------------------------------------------------------------------------
public:
	virtual void NativeConstruct() override;
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
