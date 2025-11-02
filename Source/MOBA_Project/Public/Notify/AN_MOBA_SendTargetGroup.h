// FXnRXn copyright

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "Animation/AnimNotifies/AnimNotify.h"
#include "AN_MOBA_SendTargetGroup.generated.h"

/**
 * 
 */
UCLASS()
class MOBA_PROJECT_API UAN_MOBA_SendTargetGroup : public UAnimNotify
{
	GENERATED_BODY()

	//------------------------------------------------------------------------------------------------------------------
public:
	virtual void Notify(
		USkeletalMeshComponent* MeshComp,
		UAnimSequenceBase* Animation,
		const FAnimNotifyEventReference& EventReference) override;

	//------------------------------------------------------------------------------------------------------------------
private:
	UPROPERTY(EditAnywhere, Category = "Moba|AnimNotify")
	FGameplayTag TargetGroupTag;
	
	UPROPERTY(EditAnywhere, Category = "Moba|AnimNotify")
	TArray<FName> TargetSocketName;
};
