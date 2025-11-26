// FXnRXn copyright

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GenericTeamAgentInterface.h"
#include "MOBA_MinionBarrack.generated.h"

UCLASS()
class MOBA_PROJECT_API AMOBA_MinionBarrack : public AActor
{
	GENERATED_BODY()
	//------------------------------------------------------------------------------------------------------------------
public:
	virtual void BeginPlay() override;
	
	//------------------------------------------------------------------------------------------------------------------
private:
	UPROPERTY(EditAnywhere, Category = "Moba|MinionBarrack")
	FGenericTeamId BarrackTeamID;
	
	UPROPERTY()
	TArray<class AMOBA_Minion*> MinionPool;
	
	UPROPERTY(EditAnywhere, Category = "Moba|MinionBarrack")
	TSubclassOf<class AMOBA_Minion> MinionClass;
	
	UPROPERTY(EditAnywhere, Category = "Moba|MinionBarrack")
	TArray<class APlayerStart*> SpawnSpots;
	
	int NextSpawnSpotIndex = -1;
	
	
	const APlayerStart* GetNextSpawnSpot();
	void SpawnNewMinion(int SpawnAmount);
};
