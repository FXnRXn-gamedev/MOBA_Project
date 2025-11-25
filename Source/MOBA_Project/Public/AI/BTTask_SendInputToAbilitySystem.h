// FXnRXn copyright

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "AbilitySystem/MOBA_GameplayAbilityTypes.h"
#include "BTTask_SendInputToAbilitySystem.generated.h"

/**
 * 
 */
UCLASS()
class MOBA_PROJECT_API UBTTask_SendInputToAbilitySystem : public UBTTaskNode
{
	GENERATED_BODY()
	
	//------------------------------------------------------------------------------------------------------------------
public:
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
	
	//------------------------------------------------------------------------------------------------------------------
private:
	UPROPERTY(EditAnywhere, Category = "Moba|Task")
	EMOBA_AbilityInputID AbilityInputID;
};
