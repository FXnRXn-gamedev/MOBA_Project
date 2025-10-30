// FXnRXn copyright


#include "Widgets/MOBA_GameplayWidget.h"
#include "AbilitySystemBlueprintLibrary.h"
#include "AbilitySystemComponent.h"
#include "AbilitySystem/MOBA_AttributeSet.h"
#include "Widgets/MOBA_AttributeValueGauge.h"


void UMOBA_GameplayWidget::NativeConstruct()
{
	Super::NativeConstruct();

	InitializeStatBar();
}

void UMOBA_GameplayWidget::InitializeStatBar()
{
	OwnerAbilitySystemComp = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(GetOwningPlayerPawn());
	if (!IsValid(OwnerAbilitySystemComp)) return;
	// Initialize the bars immediately
	InitHealthBar();
	InitManaBar();

	// Bind to attribute changes - this will trigger when attributes are initialized
	OwnerAbilitySystemComp->GetGameplayAttributeValueChangeDelegate(UMOBA_AttributeSet::GetHealthAttribute())
		.AddUObject(this, &UMOBA_GameplayWidget::OnHealthChanged);
		
	OwnerAbilitySystemComp->GetGameplayAttributeValueChangeDelegate(UMOBA_AttributeSet::GetManaAttribute())
		.AddUObject(this, &UMOBA_GameplayWidget::OnManaChanged);
}


void UMOBA_GameplayWidget::OnHealthChanged(const FOnAttributeChangeData& Data)
{
	InitHealthBar();
}

void UMOBA_GameplayWidget::OnManaChanged(const FOnAttributeChangeData& Data)
{
	InitManaBar();
}


void UMOBA_GameplayWidget::InitHealthBar()
{
	if (HealthBar) HealthBar->SetAndBoundToGameplayAttribute(OwnerAbilitySystemComp, UMOBA_AttributeSet::GetHealthAttribute(), UMOBA_AttributeSet::GetMaxHealthAttribute());
}

void UMOBA_GameplayWidget::InitManaBar()
{
	if (ManaBar) ManaBar->SetAndBoundToGameplayAttribute(OwnerAbilitySystemComp, UMOBA_AttributeSet::GetManaAttribute(), UMOBA_AttributeSet::GetMaxManaAttribute());
}
