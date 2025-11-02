// FXnRXn copyright


#include "AbilitySystem/MOBA_GameplayAbilityBase.h"

UAnimInstance* UMOBA_GameplayAbilityBase::GetOwnerAnimInstance() const
{
	UAnimInstance* AnimInstance = nullptr;
	USkeletalMeshComponent* OwnerSkeletalMeshComp = GetOwningComponentFromActorInfo();
	if (OwnerSkeletalMeshComp)
	{
		AnimInstance = OwnerSkeletalMeshComp->GetAnimInstance();
	}

	return AnimInstance;
}
