// FXnRXn copyright


#include "MOBA_Project/Public/Player/MOBA_PlayerController.h"

#include "Blueprint/UserWidget.h"
#include "Player/MOBA_PlayerCharacter.h"
#include "Widgets/MOBA_GameplayWidget.h"


//---> SERVER CLIENT CHAIN <---
//-----------------------------------------

void AMOBA_PlayerController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);
	
	PlayerCharacter = Cast<AMOBA_PlayerCharacter>(InPawn);
	if (!IsValid(PlayerCharacter)) return;

	PlayerCharacter->ServerSideInit();
}

void AMOBA_PlayerController::AcknowledgePossession(APawn* P)
{
	Super::AcknowledgePossession(P);

	PlayerCharacter = Cast<AMOBA_PlayerCharacter>(P);
	if (!IsValid(PlayerCharacter)) return;

	PlayerCharacter->ClientSideInit();
	SpawnGameplayWidget();
}

//---> WIDGET <---
//-----------------------------------------

void AMOBA_PlayerController::SpawnGameplayWidget()
{
	if (!IsLocalPlayerController()) return;

	GameplayWidgetInstance = CreateWidget<UMOBA_GameplayWidget>(this, GameplayWidgetClass);
	if (GameplayWidgetInstance)
	{
		GameplayWidgetInstance->AddToViewport();
	}
}
