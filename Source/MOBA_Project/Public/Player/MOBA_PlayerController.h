// FXnRXn copyright

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "GenericTeamAgentInterface.h"
#include "MOBA_PlayerController.generated.h"

class AMOBA_PlayerCharacter;
class UMOBA_GameplayWidget;



UCLASS()
class MOBA_PROJECT_API AMOBA_PlayerController : public APlayerController, public IGenericTeamAgentInterface
{
	GENERATED_BODY()

	//------------------------------------------------------------------------------------------------------------------
public:
	// Only Called on the server
	virtual void OnPossess(APawn* InPawn) override;
	// Only Called on the client, also on the listening server
	virtual void AcknowledgePossession(APawn* P) override;
	
	// Assign Team Agent to given TeamID
	virtual void SetGenericTeamId(const FGenericTeamId& NewTeamID) override;
	// Retrive Team identifier in form of FGenericTeamId
	virtual FGenericTeamId GetGenericTeamId() const override;
	
	// Setup variable to Replicate in Server
	virtual void GetLifetimeReplicatedProps(TArray<class FLifetimeProperty>& OutLifetimeProps) const override;

	//------------------------------------------------------------------------------------------------------------------
protected:

	//------------------------------------------------------------------------------------------------------------------
private:
	void SpawnGameplayWidget();
	
	// Player Refference
	UPROPERTY()
	AMOBA_PlayerCharacter* PlayerCharacter;

	// Widget
	UPROPERTY(EditDefaultsOnly, Category = "Moba|Widgets")
	TSubclassOf<UUserWidget> GameplayWidgetClass;

	UPROPERTY()
	UMOBA_GameplayWidget* GameplayWidgetInstance;
	
	
	//---> TEAM ID <---
	//-----------------------------------------
	
	// Team Agent
	UPROPERTY(Replicated)
	FGenericTeamId TeamID;
};
