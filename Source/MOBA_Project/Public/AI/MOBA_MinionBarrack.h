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
	
	//--------------------------------------------------
	// BARRACK CONFIGURATION
	//--------------------------------------------------
	UPROPERTY(EditAnywhere, Category = "Moba|MinionBarrack")
	FGenericTeamId BarrackTeamID;
	
	UPROPERTY(EditAnywhere, Category = "Moba|MinionBarrack")
	TSubclassOf<class AMOBA_Minion> MinionClass;
	
	UPROPERTY(EditAnywhere, Category = "Moba|MinionBarrack")
	TArray<class APlayerStart*> SpawnSpots;
	
	
	int NextSpawnSpotIndex = -1;
	
	
	const APlayerStart* GetNextSpawnSpot();
	void SpawnNewMinion(int SpawnAmount);
	
	
	
	//--------------------------------------------------
	// PERIODIC SPAWN
	//--------------------------------------------------
	
	UPROPERTY(EditAnywhere, Category = "Moba|MinionBarrack")
	int MinionPerGroup = 3;
	
	UPROPERTY(EditAnywhere, Category = "Moba|MinionBarrack")
	float GroupSpawnInterval = 5.f;
	
	FTimerHandle SpawnIntervalTimerHandle;
	void SpawnNewGroup();
	AMOBA_Minion* GetNextAvailableMinion() const;
	
	
	//--------------------------------------------------
	// GOAL
	//--------------------------------------------------
	
	UPROPERTY(EditAnywhere, Category = "Moba|MinionBarrack")
	AActor* GoalActor;
	
	
	//--------------------------------------------------
	// POOL MANAGEMENT
	//--------------------------------------------------
	UPROPERTY()
	TArray<class AMOBA_Minion*> MinionPool;

	
};
