// FXnRXn copyright

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "AbilitySystemInterface.h"


#include "MOBA_CharacterBase.generated.h"


class UAttributeSet;
class UMOBA_AbilitySystemComponent;



UCLASS()
class MOBA_PROJECT_API AMOBA_CharacterBase : public ACharacter, public IAbilitySystemInterface
{
	GENERATED_BODY()

	//------------------------------------------------------------------------------------------------------------------
public:
	AMOBA_CharacterBase();
	void ServerSideInit();
	void ClientSideInit();


	

	//------------------------------------------------------------------------------------------------------------------
	//--->										GAMEPLAY ABILITY													<---
	//------------------------------------------------------------------------------------------------------------------
public:

	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;
	UAttributeSet* GetAttributeSet() const{return AttributeSet;}

	//------------------------------------------------------------------------------------------------------------------
private:
	UPROPERTY(VisibleAnywhere, Category = "Moba|AbilitySystem")
	TObjectPtr<UMOBA_AbilitySystemComponent> AbilitySystemComp;
	UPROPERTY()
	TObjectPtr<UAttributeSet> AttributeSet;

	
};
