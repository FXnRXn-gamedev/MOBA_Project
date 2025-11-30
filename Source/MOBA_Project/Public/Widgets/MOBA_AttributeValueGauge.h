// FXnRXn copyright

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "GameplayEffectTypes.h"
#include "AttributeSet.h"
#include "MOBA_AttributeValueGauge.generated.h"

struct FOnAttributeChangeData;
class UAbilitySystemComponent;
class UProgressBar;
class UTextBlock;


UCLASS()
class MOBA_PROJECT_API UMOBA_AttributeValueGauge : public UUserWidget
{
	GENERATED_BODY()

	//------------------------------------------------------------------------------------------------------------------
public:
	virtual void NativePreConstruct() override;
	void SetAndBoundToGameplayAttribute(UAbilitySystemComponent* AbilitySystemComp, const FGameplayAttribute& Attribute, const FGameplayAttribute& MaxAttribute);
	void SetValue(float NewValue, float MaxValue);


	//------------------------------------------------------------------------------------------------------------------
private:
	void ValueChanged(const FOnAttributeChangeData& ChangeData);
	void MaxValueChanged(const FOnAttributeChangeData& ChangeData);

	float CachedValue;
	float CachedMaxValue;


	//--------------------------------------------------
	// WIDGET ATTRIBUTE
	//--------------------------------------------------
	
	UPROPERTY(EditAnywhere, Category = "Moba|Widgets|Attributes")
	FLinearColor BarColor;
	
	UPROPERTY(EditAnywhere, Category = "Moba|Widgets|Attributes")
	FSlateFontInfo ValueTextFont;
	
	UPROPERTY(EditAnywhere, Category = "Moba|Widgets|Attributes")
	bool bValueTextVisible = true;
	
	UPROPERTY(EditAnywhere, Category = "Moba|Widgets|Attributes")
	bool bProgressBarVisible = true;
	
	UPROPERTY(VisibleAnywhere, meta = (BindWidget))
	UProgressBar* ProgressBar;

	UPROPERTY(VisibleAnywhere, meta = (BindWidget))
	UTextBlock* ValueText;
};
