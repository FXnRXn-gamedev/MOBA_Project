// FXnRXn copyright

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "GenericTeamAgentInterface.h"
#include "MOBA_GameMode.generated.h"


UCLASS()
class MOBA_PROJECT_API AMOBA_GameMode : public AGameModeBase
{
	GENERATED_BODY()
	
	//------------------------------------------------------------------------------------------------------------------
public:
	virtual APlayerController* SpawnPlayerController(ENetRole InRemoteRole, const FString& Options) override;
	
	//------------------------------------------------------------------------------------------------------------------
private:
	FGenericTeamId GetTeamIDForPlayer(const APlayerController* PlayerController) const;
	AActor* FindNextStartSpotForTeam(const FGenericTeamId& TeamID) const;
	
	UPROPERTY(EditDefaultsOnly, Category="Moba|Team")
	TMap<FGenericTeamId , FName> TeamStartSpotTagMap;
	
	
};
