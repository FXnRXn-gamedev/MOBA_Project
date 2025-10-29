// FXnRXn copyright


#include "MOBA_Project/Public/Player/MOBA_PlayerController.h"

#include "Player/MOBA_PlayerCharacter.h"

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
}
