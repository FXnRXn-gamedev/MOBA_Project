// FXnRXn copyright


#include "Widgets/MOBA_OverHeadStats.h"
#include "AbilitySystemBlueprintLibrary.h"
#include "AbilitySystemComponent.h"
#include "AbilitySystem/MOBA_AttributeSet.h"
#include "Widgets/MOBA_AttributeValueGauge.h"





void UMOBA_OverHeadStats::ConfigureWithASC(UAbilitySystemComponent* AbilitySystemComponent)
{
	OwnerAbilitySystemComp = AbilitySystemComponent;
	
	if (OwnerAbilitySystemComp)
	{
		InitializeStatBar();
	}
	
	
}

void UMOBA_OverHeadStats::InitializeStatBar()
{
	InitHealthBar();
	InitManaBar();
	
	// Bind to attribute changes - this will trigger when attributes are initialized
	OwnerAbilitySystemComp->GetGameplayAttributeValueChangeDelegate(UMOBA_AttributeSet::GetHealthAttribute())
		.AddUObject(this, &UMOBA_OverHeadStats::OnHealthChanged);
		
	OwnerAbilitySystemComp->GetGameplayAttributeValueChangeDelegate(UMOBA_AttributeSet::GetManaAttribute())
		.AddUObject(this, &UMOBA_OverHeadStats::OnManaChanged);
}

void UMOBA_OverHeadStats::OnHealthChanged(const FOnAttributeChangeData& Data)
{
	InitHealthBar();
}

void UMOBA_OverHeadStats::OnManaChanged(const FOnAttributeChangeData& Data)
{
	InitManaBar();
}

void UMOBA_OverHeadStats::InitHealthBar()
{
	if (HealthBar) HealthBar->SetAndBoundToGameplayAttribute(OwnerAbilitySystemComp, UMOBA_AttributeSet::GetHealthAttribute(), UMOBA_AttributeSet::GetMaxHealthAttribute());
}

void UMOBA_OverHeadStats::InitManaBar()
{
	if (ManaBar) ManaBar->SetAndBoundToGameplayAttribute(OwnerAbilitySystemComp, UMOBA_AttributeSet::GetManaAttribute(), UMOBA_AttributeSet::GetMaxManaAttribute());
}
