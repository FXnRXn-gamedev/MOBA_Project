// FXnRXn copyright


#include "AI/MOBA_Minion.h"

#include "AbilitySystemComponent.h"
#include "AbilitySystem/MOBA_AbilitySystemStatics.h"


void AMOBA_Minion::SetGenericTeamId(const FGenericTeamId& NewTeamID)
{
	Super::SetGenericTeamId(NewTeamID);
	PickSkinBasedOnTeamId();
}

bool AMOBA_Minion::IsActive() const
{
	return !GetAbilitySystemComponent()->HasMatchingGameplayTag(UMOBA_AbilitySystemStatics::GetDeadStatTag());
}

void AMOBA_Minion::Activate()
{
	GetAbilitySystemComponent()->RemoveActiveEffectsWithGrantedTags(FGameplayTagContainer(UMOBA_AbilitySystemStatics::GetDeadStatTag()));
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

