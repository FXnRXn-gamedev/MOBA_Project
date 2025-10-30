// FXnRXn copyright

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "MOBA_PlayerController.generated.h"

class AMOBA_PlayerCharacter;
class UMOBA_GameplayWidget;



UCLASS()
class MOBA_PROJECT_API AMOBA_PlayerController : public APlayerController
{
	GENERATED_BODY()

	//------------------------------------------------------------------------------------------------------------------
public:
	// Only Called on the server
	virtual void OnPossess(APawn* InPawn) override;
	// Only Called on the client, also on the listening server
	virtual void AcknowledgePossession(APawn* P) override;

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
};
