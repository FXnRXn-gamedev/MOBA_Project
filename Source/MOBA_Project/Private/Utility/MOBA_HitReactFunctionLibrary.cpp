// FXnRXn copyright


#include "Utility/MOBA_HitReactFunctionLibrary.h"

EHitReactDirection UMOBA_HitReactFunctionLibrary::GetHitReactDirection(const FVector& TargetForward,
	const FVector& ToInstigator)
{
	const float Dot = FVector::DotProduct(TargetForward, ToInstigator);

	if (Dot < -0.5f)
	{
		return EHitReactDirection::back;
	}
	
	if (Dot < 0.5f)
	{
		// Either Left or Right
		const FVector Cross = FVector::CrossProduct(TargetForward, ToInstigator);
		if (Cross.Z > 0.f)
		{
			return EHitReactDirection::right;
		}
		else
		{
			return EHitReactDirection::left;
		}
	}
	return EHitReactDirection::forward;
}

FName UMOBA_HitReactFunctionLibrary::GetHitReactDirectionName(const EHitReactDirection& Direction)
{
	switch (Direction)
	{
	case EHitReactDirection::left:		return FName("Left");
	case EHitReactDirection::right:		return FName("Right");
	case EHitReactDirection::forward:	return FName("Forward");
	case EHitReactDirection::back:		return FName("Back");
	default:							return FName("None");
	}
}
