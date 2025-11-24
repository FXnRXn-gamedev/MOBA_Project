// FXnRXn copyright


#include "AI/MOBA_AIController.h"

#include "BehaviorTree/BlackboardComponent.h"
#include "Character/MOBA_CharacterBase.h"
#include "AbilitySystemBlueprintLibrary.h"
#include "AbilitySystemComponent.h"
#include "AbilitySystem/MOBA_AbilitySystemStatics.h"
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
	
	// Find Target
	AIPerceptionComponent->OnTargetPerceptionUpdated.AddDynamic(this, &ThisClass::TargetPerceptionUpdated);
	
	// When Player outside of the range , AI  can remember
	AIPerceptionComponent->OnTargetPerceptionForgotten.AddDynamic(this, &ThisClass::TargetForgotten);
}




//---> UNREAL CALLBACK <---
//-----------------------------------------

void AMOBA_AIController::BeginPlay()
{
	Super::BeginPlay();
	RunBehaviorTree(AIBehaviorTree);
}

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







//---> AI PERCEPTION BEHAVIOUR <---
//-----------------------------------------

void AMOBA_AIController::TargetPerceptionUpdated(AActor* TargetActor, FAIStimulus Stimulus)
{
	if (Stimulus.WasSuccessfullySensed())
	{
		if (!GetCurrentTarget())
		{
			SetActorTarget(TargetActor);
		}
	}
	else
	{
		//if (GetCurrentTarget() == TargetActor) SetActorTarget(nullptr);
		ForgetActorIfDead(TargetActor);
	}
}

void AMOBA_AIController::TargetForgotten(AActor* ForgottenActor)
{
	if (!ForgottenActor) return;
	if (GetCurrentTarget() == ForgottenActor)
	{
		SetActorTarget(GetNextPercievedActor());
	}
}

const UObject* AMOBA_AIController::GetCurrentTarget() const
{
	const UBlackboardComponent* BlackboardComponent = GetBlackboardComponent();
	if (!BlackboardComponent) return nullptr;
	if (!BlackboardComponent->GetValueAsObject(TargetBlackboardKeyName)) return nullptr;
	
	return GetBlackboardComponent()->GetValueAsObject(TargetBlackboardKeyName);
}

void AMOBA_AIController::SetActorTarget(AActor* NewTargetActor)
{
	// if (!IsValid(NewTargetActor)) return;
	// if (NewTargetActor == GetCurrentTarget()) return;
	
	UBlackboardComponent* BlackboardComponent = GetBlackboardComponent();
	if (!BlackboardComponent) return;

	if (NewTargetActor)
	{
		BlackboardComponent->SetValueAsObject(TargetBlackboardKeyName, NewTargetActor);
	}
	else
	{
		BlackboardComponent->ClearValue(TargetBlackboardKeyName);
	}
	
}

AActor* AMOBA_AIController::GetNextPercievedActor() const
{
	if (PerceptionComponent)
	{
		TArray<AActor*> Actors;
		AIPerceptionComponent->GetPerceivedHostileActors(Actors);
		return Actors.Num() != 0 ? Actors[0] : nullptr;
	}
	return nullptr;
}

void AMOBA_AIController::ForgetActorIfDead(AActor* ActorToForget)
{
	const UAbilitySystemComponent* ActorASC = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(ActorToForget);
	if (!ActorASC) return;

	if (ActorASC->HasMatchingGameplayTag(UMOBA_AbilitySystemStatics::GetDeadStatTag()))
	{
		for (UAIPerceptionComponent::TActorPerceptionContainer::TIterator Iter = AIPerceptionComponent->GetPerceptualDataIterator(); Iter; ++Iter)
		{
			if (Iter->Key != ActorToForget)
			{
				continue;
			}
			for (FAIStimulus& Stimulus : Iter->Value.LastSensedStimuli)
			{
				Stimulus.SetStimulusAge(TNumericLimits<float>::Max());
			}
		}
	}
	
}

