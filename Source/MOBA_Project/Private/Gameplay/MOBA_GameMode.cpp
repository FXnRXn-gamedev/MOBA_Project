// FXnRXn copyright


#include "MOBA_Project/Public/Gameplay/MOBA_GameMode.h"
#include "GameFramework/PlayerStart.h"
#include "EngineUtils.h"

APlayerController* AMOBA_GameMode::SpawnPlayerController(ENetRole InRemoteRole, const FString& Options)
{
	// Spawn Player Controller
	APlayerController* NewPlayerController = Super::SpawnPlayerController(InRemoteRole, Options);
	IGenericTeamAgentInterface* NewPlayerTeamInterface = Cast<IGenericTeamAgentInterface>(NewPlayerController);
	FGenericTeamId TeamId = GetTeamIDForPlayer(NewPlayerController);
	if (NewPlayerTeamInterface)
	{
		NewPlayerTeamInterface->SetGenericTeamId(TeamId);
	}
	
	NewPlayerController->StartSpot = FindNextStartSpotForTeam(TeamId);
	return NewPlayerController;
}

FGenericTeamId AMOBA_GameMode::GetTeamIDForPlayer(const APlayerController* PlayerController) const
{
	static int PlayerCount = 0;
	++PlayerCount;
	return FGenericTeamId(PlayerCount % 2);
}

AActor* AMOBA_GameMode::FindNextStartSpotForTeam(const FGenericTeamId& TeamID) const
{
	const FName* StartSpotTag = TeamStartSpotTagMap.Find(TeamID); 
	if (!StartSpotTag) return nullptr;
	
	UWorld* World = GetWorld();
	if (!World) return nullptr;

	for (TActorIterator<APlayerStart> It(World); It; ++It)
	{
		if (It->PlayerStartTag == *StartSpotTag)
		{
			It->PlayerStartTag = FName("Taken");
			return *It;
		}
	}
	
	return nullptr;
}
