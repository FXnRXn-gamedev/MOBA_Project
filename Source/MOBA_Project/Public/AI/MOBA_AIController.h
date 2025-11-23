// FXnRXn copyright

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "MOBA_AIController.generated.h"


class UAIPerceptionComponent;
class UAISenseConfig_Sight;




UCLASS()
class MOBA_PROJECT_API AMOBA_AIController : public AAIController
{
	GENERATED_BODY()

	//------------------------------------------------------------------------------------------------------------------
public:
	AMOBA_AIController();
	virtual void OnPossess(APawn* InPawn) override;

	//------------------------------------------------------------------------------------------------------------------
private:
	UPROPERTY(VisibleDefaultsOnly, Category="Moba|AIPerception")
	UAIPerceptionComponent* AIPerceptionComponent;
	
	UPROPERTY(VisibleDefaultsOnly, Category="Moba|AIPerception")
	UAISenseConfig_Sight* SightConfig;
	
};
