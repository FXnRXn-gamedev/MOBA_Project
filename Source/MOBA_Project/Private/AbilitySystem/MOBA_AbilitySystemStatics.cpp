// FXnRXn copyright


#include "AbilitySystem/MOBA_AbilitySystemStatics.h"
#include "GameplayTag/MOBA_GameplayTags.h"


FGameplayTag UMOBA_AbilitySystemStatics::GetBasicAttackAbilityTag()
{
	return FGameplayTag::RequestGameplayTag("MOBA_Tags.MOBA_Abilities.MOBA_BasicAbilities.BasicAttack1");
}
