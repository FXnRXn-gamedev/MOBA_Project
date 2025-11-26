// FXnRXn copyright


#include "AI/MOBA_Minion.h"


void AMOBA_Minion::SetGenericTeamId(const FGenericTeamId& NewTeamID)
{
	Super::SetGenericTeamId(NewTeamID);
	PickSkinBasedOnTeamId();
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

