// FXnRXn copyright

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "MOBA_AIController.generated.h"

class UBehaviorTree;
class UAIPerceptionComponent;
class UAISenseConfig_Sight;

struct FAIStimulus;


UCLASS()
class MOBA_PROJECT_API AMOBA_AIController : public AAIController
{
	GENERATED_BODY()

	//------------------------------------------------------------------------------------------------------------------
public:
	AMOBA_AIController();
	virtual void BeginPlay() override;
	
	
	
	
	virtual void OnPossess(APawn* InPawn) override;
	
	
	//------------------------------------------------------------------------------------------------------------------
private:
	UPROPERTY(EditDefaultsOnly, Category="Moba|AIBehaviour")
	FName TargetBlackboardKeyName = "Target";
	
	UPROPERTY(EditDefaultsOnly, Category="Moba|AIBehaviour")
	UBehaviorTree* AIBehaviorTree;
	
	UPROPERTY(VisibleDefaultsOnly, Category="Moba|AIPerception")
	UAIPerceptionComponent* AIPerceptionComponent;
	
	UPROPERTY(VisibleDefaultsOnly, Category="Moba|AIPerception")
	UAISenseConfig_Sight* SightConfig;
	
	UFUNCTION()
	void TargetPerceptionUpdated(AActor* TargetActor, FAIStimulus Stimulus);
	
	UFUNCTION()
	void TargetForgotten(AActor* ForgottenActor);
	
	const UObject* GetCurrentTarget() const;
	void SetActorTarget(AActor* NewTargetActor);
	AActor* GetNextPercievedActor() const;
	
	void ForgetActorIfDead(AActor* ActorToForget);
	
};

