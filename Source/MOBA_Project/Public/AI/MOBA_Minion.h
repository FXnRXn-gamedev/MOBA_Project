// FXnRXn copyright

#pragma once

#include "CoreMinimal.h"
#include "Character/MOBA_CharacterBase.h"
#include "MOBA_Minion.generated.h"

UCLASS()
class MOBA_PROJECT_API AMOBA_Minion : public AMOBA_CharacterBase
{
	GENERATED_BODY()

	//------------------------------------------------------------------------------------------------------------------
public:
	virtual void SetGenericTeamId(const FGenericTeamId& NewTeamID) override;
	
	bool IsActive() const;
	void Activate();
	
	void SetGoal(AActor* GoalActor);
	//------------------------------------------------------------------------------------------------------------------
private:
	UPROPERTY(EditDefaultsOnly, Category= "Moba|AI")
	FName GoalBlackboardKeyName = "Goal";
	
	UPROPERTY(EditDefaultsOnly, Category= "Moba|Visual")
	TMap<FGenericTeamId, USkeletalMesh*> SkinMap;
	
	void PickSkinBasedOnTeamId();
	virtual void OnRep_TeamID() override;
};
