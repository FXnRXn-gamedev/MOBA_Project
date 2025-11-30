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
		InitializeMinionPool();
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
	int SuccessfulSpawns = 0;
	
	for (int i = 0; i < MinionPerGroup; ++i)
	{
		// Get minion from pool
		AMOBA_Minion* AvailableMinion = GetInactiveMinion();
		if (!AvailableMinion)
		{
			if (bAllowPoolGrowth)
			{
				AvailableMinion = SpawnMinionForPool();
			}
			else
			{
				break; // No more minions available and growth is disabled
			}
		}
		
		if (AvailableMinion)
		{
			// Setup spawn transform
			FTransform SpawnTransform = GetActorTransform();
			if (const APlayerStart* NextSpawnSpot = GetNextSpawnSpot())
			{
				SpawnTransform = NextSpawnSpot->GetActorTransform();
			}
			
			// Reactivate minion at spawn location
			AvailableMinion->SetActorTransform(SpawnTransform);
			AvailableMinion->Activate();
			AvailableMinion->SetGoal(GoalActor);
			
			++SuccessfulSpawns;
		}
	}
	
	// int i = MinionPerGroup;
	// while (i > 0)
	// {
	// 	FTransform SpawnTransform =  GetActorTransform();
	// 	if (const APlayerStart* NextSpawnSpot = GetNextSpawnSpot()) SpawnTransform = NextSpawnSpot->GetActorTransform();
	// 	
	// 	AMOBA_Minion* NextAvailableMinion = GetNextAvailableMinion();
	// 	if(!NextAvailableMinion) break;
	// 	
	// 	NextAvailableMinion->SetActorTransform(SpawnTransform);
	// 	NextAvailableMinion->Activate();
	// 	--i;
	// }
	//
	// SpawnNewMinion(i);
}

AMOBA_Minion* AMOBA_MinionBarrack::GetNextAvailableMinion() const
{
	for (AMOBA_Minion* Minion : MinionPool)
	{
		if (!Minion->IsActive()) return Minion;
	}
	
	return nullptr;
}



//--------------------------------------------------
// POOL MANAGEMENT
//--------------------------------------------------

void AMOBA_MinionBarrack::InitializeMinionPool()
{
	if (!HasAuthority()) return;
	
	MinionPool.Reserve(InitialPoolSize);
	
	for (int32 i = 0; i < InitialPoolSize; ++i)
	{
		AMOBA_Minion* NewMinion = SpawnMinionForPool();
		if (NewMinion)
		{
			// Keep minion inactive initially
			NewMinion->SetActorHiddenInGame(true);
			NewMinion->SetActorEnableCollision(false);
		}
	}
}

AMOBA_Minion* AMOBA_MinionBarrack::SpawnMinionForPool()
{
	if (!HasAuthority() || !MinionClass) return nullptr;
	
	// Spawn off-map initially
	FVector HiddenLocation = GetActorLocation() + FVector(0.f, 0.f, -10000.f);
	FTransform SpawnTransform = FTransform(FRotator::ZeroRotator, HiddenLocation);
	
	AMOBA_Minion* NewMinion = GetWorld()->SpawnActorDeferred<AMOBA_Minion>(
		MinionClass,
		SpawnTransform,
		this,
		nullptr,
		ESpawnActorCollisionHandlingMethod::AlwaysSpawn
	);
	
	if (NewMinion)
	{
		NewMinion->SetGenericTeamId(BarrackTeamID);
		NewMinion->FinishSpawning(SpawnTransform);
		MinionPool.Add(NewMinion);
		
		return NewMinion;
	}
	return nullptr;
}

AMOBA_Minion* AMOBA_MinionBarrack::GetInactiveMinion()
{
	for (AMOBA_Minion* Minion : MinionPool)
	{
		if (Minion && !Minion->IsActive())
		{
			return Minion;
		}
	}
	return nullptr;
}

void AMOBA_MinionBarrack::ReturnMinionToPool(AMOBA_Minion* Minion)
{
	if (!Minion || !HasAuthority()) return;
	
	// Hide and disable the minion
	Minion->SetActorHiddenInGame(true);
	Minion->SetActorEnableCollision(false);
	
	// Move off-map
	FVector HiddenLocation = GetActorLocation() + FVector(0.f, 0.f, -10000.f);
	Minion->SetActorLocation(HiddenLocation);
}








