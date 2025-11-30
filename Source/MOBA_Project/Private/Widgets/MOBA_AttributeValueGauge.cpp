// FXnRXn copyright


#include "Widgets/MOBA_AttributeValueGauge.h"

#include "AbilitySystemComponent.h"
#include "Components/ProgressBar.h"
#include "Components/TextBlock.h"

void UMOBA_AttributeValueGauge::NativePreConstruct()
{
	Super::NativePreConstruct();

	// Init Progress Bar Color
	ProgressBar->SetFillColorAndOpacity(BarColor);
	
	//Init visibility
	ValueText->SetFont(ValueTextFont);
	ValueText->SetVisibility(bValueTextVisible ? ESlateVisibility::Visible : ESlateVisibility::Hidden);
	ProgressBar->SetVisibility(bProgressBarVisible ? ESlateVisibility::Visible : ESlateVisibility::Hidden);
}



void UMOBA_AttributeValueGauge::SetAndBoundToGameplayAttribute(UAbilitySystemComponent* AbilitySystemComp,
                                                               const FGameplayAttribute& Attribute, const FGameplayAttribute& MaxAttribute)
{
	if (!IsValid(AbilitySystemComp)) return;
	
	bool bFoundAttribute = false;
	float Value = AbilitySystemComp->GetGameplayAttributeValue(Attribute, bFoundAttribute);
	float MaxValue = AbilitySystemComp->GetGameplayAttributeValue(MaxAttribute, bFoundAttribute);
	
	if (bFoundAttribute)
	{
		SetValue(Value, MaxValue);
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Attribute Value Gauge : %s , Attribute not found"), *GetName());
	}

	//AbilitySystemComp->GetGameplayAttributeValueChangeDelegate(Attribute).AddUFunction(this, FName("ValueChanged"));
	//AbilitySystemComp->GetGameplayAttributeValueChangeDelegate(MaxAttribute).AddUFunction(this, FName("MaxValueChanged"));
	
}



//--------------------------------------------------
// WIDGET VALUE CHANGE/SET
//--------------------------------------------------

void UMOBA_AttributeValueGauge::ValueChanged(const FOnAttributeChangeData& ChangeData)
{
	SetValue(ChangeData.NewValue, CachedMaxValue);
}

void UMOBA_AttributeValueGauge::MaxValueChanged(const FOnAttributeChangeData& ChangeData)
{
	SetValue(CachedValue, ChangeData.NewValue);
}

void UMOBA_AttributeValueGauge::SetValue(float NewValue, float MaxValue)
{
	CachedValue = NewValue;
	CachedMaxValue = MaxValue;
	
	if (MaxValue == 0.0f)
	{
		UE_LOG(LogTemp, Warning, TEXT("Attribute Value Gauge : %s , MaxValue can't be 0.0f"), *GetName());
		return;
	}
	
	float NewPercent = NewValue / MaxValue;
	ProgressBar->SetPercent(NewPercent);

	FNumberFormattingOptions FormatOptions = FNumberFormattingOptions().SetMinimumFractionalDigits(0);
	ValueText->SetText(
		FText::Format(
			FTextFormat::FromString("{0}%"),
			FText::AsNumber(NewValue, &FormatOptions)
		));
}

