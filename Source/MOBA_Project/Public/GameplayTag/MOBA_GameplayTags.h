// FXnRXn copyright

#pragma once

#include "CoreMinimal.h"
#include "NativeGameplayTags.h"


namespace MOBA_Tags
{
	namespace MOBA_Abilities
	{
		namespace MOBA_BasicAbilities
		{
			UE_DECLARE_GAMEPLAY_TAG_EXTERN(BasicAttack1)
		}
	}

	namespace MOBA_Events
	{
		namespace PlayerEvent
		{
			UE_DECLARE_GAMEPLAY_TAG_EXTERN(ComboAttack1)
			UE_DECLARE_GAMEPLAY_TAG_EXTERN(ComboAttack2)
			UE_DECLARE_GAMEPLAY_TAG_EXTERN(ComboAttack3)
			UE_DECLARE_GAMEPLAY_TAG_EXTERN(ComboAttack4)
			UE_DECLARE_GAMEPLAY_TAG_EXTERN(ComboAttackEnd)

			UE_DECLARE_GAMEPLAY_TAG_EXTERN(Damage)
		}
	}
}
