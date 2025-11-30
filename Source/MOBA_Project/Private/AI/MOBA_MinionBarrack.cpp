// FXnRXn copyright


#include "AI/MOBA_MinionBarrack.h"

#include "AI/MOBA_Minion.h"
#include "GameFramework/PlayerStart.h"

//--------------------------------------------------
// UNREAL CALLBACK
//--------------------------------------------------

void AMOBA_MinionBarrack::BeginPlay()
{
	Super::BeginPlay();
	if (HasAuthority())
	{
		//--> [DEBUG TESTING] : SpawnNewMinion(5);
		GetWorldTimerManager().SetTimer(SpawnIntervalTimerHandle, this, &ThisClass::SpawnNewGroup, GroupSpawnInterval, true);
	}
	
}



//--------------------------------------------------
// SPAWN CONFIGURATION
//--------------------------------------------------

const APlayerStart* AMOBA_MinionBarrack::GetNextSpawnSpot()
{
	if (SpawnSpots.Num() == 0) return nullptr;
	++NextSpawnSpotIndex;
	if (NextSpawnSpotIndex >= SpawnSpots.Num()) NextSpawnSpotIndex = 0;
	return SpawnSpots[NextSpawnSpotIndex];
}

void AMOBA_MinionBarrack::SpawnNewMinion(int SpawnAmount)
{
	for (int i = 0; i < SpawnAmount; ++i)
	{
		FTransform SpawnTransform =  GetActorTransform();
		if (const APlayerStart* NextSpawnSpot = GetNextSpawnSpot()) SpawnTransform = NextSpawnSpot->GetActorTransform();
		
		AMOBA_Minion* NewMinion = GetWorld()->SpawnActorDeferred<AMOBA_Minion>(MinionClass, SpawnTransform, this, nullptr, ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn);
		NewMinion->SetGenericTeamId(BarrackTeamID);
		NewMinion->FinishSpawning(SpawnTransform);
		NewMinion->SetGoal(GoalActor);
		MinionPool.Add(NewMinion);
	}
}




//--------------------------------------------------
// PERIODIC SPAWN GROUP
//--------------------------------------------------

void AMOBA_MinionBarrack::SpawnNewGroup()
{
	
	int i = MinionPerGroup;
	while (i > 0)
	{
		FTransform SpawnTransform =  GetActorTransform();
		if (const APlayerStart* NextSpawnSpot = GetNextSpawnSpot()) SpawnTransform = NextSpawnSpot->GetActorTransform();
		
		AMOBA_Minion* NextAvailableMinion = GetNextAvailableMinion();
		if(!NextAvailableMinion) break;
		
		NextAvailableMinion->SetActorTransform(SpawnTransform);
		NextAvailableMinion->Activate();
		--i;
	}
	
	SpawnNewMinion(i);
}

AMOBA_Minion* AMOBA_MinionBarrack::GetNextAvailableMinion() const
{
	for (AMOBA_Minion* Minion : MinionPool)
	{
		if (!Minion->IsActive()) return Minion;
	}
	
	return nullptr;
}








