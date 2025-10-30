// FXnRXn copyright

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "AbilitySystemInterface.h"


#include "MOBA_CharacterBase.generated.h"


class UAttributeSet;
class UMOBA_AbilitySystemComponent;
class UWidgetComponent;


UCLASS()
class MOBA_PROJECT_API AMOBA_CharacterBase : public ACharacter, public IAbilitySystemInterface
{
	GENERATED_BODY()

	//------------------------------------------------------------------------------------------------------------------
public:
	AMOBA_CharacterBase();
	virtual void BeginPlay() override;
	
	void ServerSideInit();
	void ClientSideInit();

	//------------------------------------------------------------------------------------------------------------------
	//--->										GAMEPLAY ABILITY													<---
	//------------------------------------------------------------------------------------------------------------------
	
public:
	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;
	UAttributeSet* GetAttributeSet() const{return AttributeSet;}

private:
	UPROPERTY(VisibleAnywhere, Category = "Moba|AbilitySystem")
	TObjectPtr<UMOBA_AbilitySystemComponent> AbilitySystemComp;
	
	UPROPERTY()
	TObjectPtr<UAttributeSet> AttributeSet;
	


	//------------------------------------------------------------------------------------------------------------------
	//--->										UI																	<---
	//------------------------------------------------------------------------------------------------------------------

private:
	UPROPERTY(VisibleDefaultsOnly, Category = "Moba|Widget")
	UWidgetComponent* OverHeadWidgetComponent;
	

	void ConfigureOverHeadWidget();
};
