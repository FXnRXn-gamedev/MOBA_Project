// FXnRXn copyright


#include "AI/MOBA_MinionBarrack.h"

#include "AI/MOBA_Minion.h"
#include "GameFramework/PlayerStart.h"


void AMOBA_MinionBarrack::BeginPlay()
{
	Super::BeginPlay();
	SpawnNewMinion(5);
}

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
		MinionPool.Add(NewMinion);
	}
}
