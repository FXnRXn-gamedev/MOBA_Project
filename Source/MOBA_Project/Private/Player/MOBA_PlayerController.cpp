// FXnRXn copyright


#include "MOBA_Project/Public/Player/MOBA_PlayerController.h"

#include "Blueprint/UserWidget.h"
#include "Net/UnrealNetwork.h"
#include "Player/MOBA_PlayerCharacter.h"
#include "Widgets/MOBA_GameplayWidget.h"


//---> SERVER CLIENT CHAIN <---
//-----------------------------------------

// Server
void AMOBA_PlayerController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);
	
	PlayerCharacter = Cast<AMOBA_PlayerCharacter>(InPawn);
	if (!IsValid(PlayerCharacter)) return;

	PlayerCharacter->ServerSideInit();
	PlayerCharacter->SetGenericTeamId(TeamID);
}

// Client
void AMOBA_PlayerController::AcknowledgePossession(APawn* P)
{
	Super::AcknowledgePossession(P);

	PlayerCharacter = Cast<AMOBA_PlayerCharacter>(P);
	if (!IsValid(PlayerCharacter)) return;

	PlayerCharacter->ClientSideInit();
	SpawnGameplayWidget();
}



//---> TEAM ID SETUP <---
//-----------------------------------------


void AMOBA_PlayerController::SetGenericTeamId(const FGenericTeamId& NewTeamID)
{
	TeamID = NewTeamID;
}

FGenericTeamId AMOBA_PlayerController::GetGenericTeamId() const
{
	return TeamID;
}

void AMOBA_PlayerController::GetLifetimeReplicatedProps(TArray<class FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME(AMOBA_PlayerController, TeamID);
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
