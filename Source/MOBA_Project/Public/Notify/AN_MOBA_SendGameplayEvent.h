// FXnRXn copyright

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotify.h"
#include "GameplayTagContainer.h"
#include "AN_MOBA_SendGameplayEvent.generated.h"






UCLASS()
class MOBA_PROJECT_API UAN_MOBA_SendGameplayEvent : public UAnimNotify
{
	GENERATED_BODY()

	//------------------------------------------------------------------------------------------------------------------
public:
	virtual void Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference) override;
	

	//------------------------------------------------------------------------------------------------------------------
private:
	UPROPERTY(EditAnywhere, Category = "Moba|AnimNotify")
	FGameplayTag EventTag;

	virtual FString GetNotifyName_Implementation() const override;
};
