// FXnRXn copyright


#include "AI/MOBA_Minion.h"
#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"




void AMOBA_Minion::SetGenericTeamId(const FGenericTeamId& NewTeamID)
{
	Super::SetGenericTeamId(NewTeamID);
	PickSkinBasedOnTeamId();
}

bool AMOBA_Minion::IsActive() const
{
	//return !GetAbilitySystemComponent()->HasMatchingGameplayTag(UMOBA_AbilitySystemStatics::GetDeadStatTag());
	return !IsDead();
}

void AMOBA_Minion::Activate()
{
	//GetAbilitySystemComponent()->RemoveActiveEffectsWithGrantedTags(FGameplayTagContainer(UMOBA_AbilitySystemStatics::GetDeadStatTag()));
	RespawnImmediately();
}



void AMOBA_Minion::PickSkinBasedOnTeamId()
{
	USkeletalMesh** Skin = SkinMap.Find(GetGenericTeamId());
	if (Skin == nullptr) return;
	
	GetMesh()->SetSkeletalMesh(*Skin);
}

void AMOBA_Minion::OnRep_TeamID()
{
	PickSkinBasedOnTeamId();
}


//--------------------------------
// --> SET GOAL <--

void AMOBA_Minion::SetGoal(AActor* GoalActor)
{
	if (AAIController* AIController = GetController<AAIController>())
	{
		if (UBlackboardComponent* BlackboardComponent = AIController->GetBlackboardComponent())
		{
			BlackboardComponent->SetValueAsObject(GoalBlackboardKeyName, GoalActor);
		}
	}
}


