// FXnRXn copyright


#include "AI/MOBA_AIController.h"

#include "Character/MOBA_CharacterBase.h"
#include "Perception/AIPerceptionComponent.h"
#include "Perception/AISenseConfig_Sight.h"


//---> CONSTRUCTOR <---
//-----------------------------------------


AMOBA_AIController::AMOBA_AIController()
{
	// Create AIPerceptionComponent
	AIPerceptionComponent = CreateDefaultSubobject<UAIPerceptionComponent>(TEXT("AIPerceptionComponent"));
	SetPerceptionComponent(*AIPerceptionComponent);
	
	// Create SightConfig
	SightConfig = CreateDefaultSubobject<UAISenseConfig_Sight>(TEXT("SightConfig"));
	
	// Configure SightConfig parameters
	SightConfig->SightRadius = 1000.0f;
	SightConfig->LoseSightRadius = 1200.0f;
	SightConfig->PeripheralVisionAngleDegrees = 180.0f;
	SightConfig->SetMaxAge(5.0f);
	
	// Configure Detection by Affiliation
	SightConfig->DetectionByAffiliation.bDetectEnemies = true;
	SightConfig->DetectionByAffiliation.bDetectNeutrals = false;
	SightConfig->DetectionByAffiliation.bDetectFriendlies = false;
	
	// Add SightConfig to AIPerceptionComponent
	AIPerceptionComponent->ConfigureSense(*SightConfig);
}


//---> UNREAL CALLBACK <---
//-----------------------------------------

void AMOBA_AIController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);
	SetGenericTeamId(FGenericTeamId(0));
	
	IGenericTeamAgentInterface* PawnAsTeamAgentInterface = Cast<IGenericTeamAgentInterface>(InPawn);
	if (PawnAsTeamAgentInterface)
	{
		PawnAsTeamAgentInterface->SetGenericTeamId(GetGenericTeamId());
	}
}

