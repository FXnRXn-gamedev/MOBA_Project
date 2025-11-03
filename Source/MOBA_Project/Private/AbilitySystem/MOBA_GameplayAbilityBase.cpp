// FXnRXn copyright


#include "AbilitySystem/MOBA_GameplayAbilityBase.h"
#include "Components/SkeletalMeshComponent.h"
#include "Kismet/KismetSystemLibrary.h"

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

TArray<FHitResult> UMOBA_GameplayAbilityBase::GetHitResultFromSweepLocationTargetData(const FGameplayAbilityTargetDataHandle& TargetDataHandle, float SphereSweepRadius, bool bIgnoreSelf) const
{
	TArray<FHitResult> OutHitResults;
	TSet<AActor*> HitActors;

	for (const TSharedPtr<FGameplayAbilityTargetData> TargetData : TargetDataHandle.Data)
	{
		FVector StartLoc = TargetData->GetOrigin().GetTranslation();
		FVector EndLoc = TargetData->GetEndPoint();
		TArray<TEnumAsByte<EObjectTypeQuery>> ObjectTypes;
		ObjectTypes.Add(UEngineTypes::ConvertToObjectType(ECC_Pawn));
		TArray<AActor*> ActorsToIgnore;
		if (bIgnoreSelf)
		{
			ActorsToIgnore.Add(GetAvatarActorFromActorInfo());
		}
		EDrawDebugTrace::Type DrawDebugType = bDebugDamageSweep ? EDrawDebugTrace::ForDuration : EDrawDebugTrace::None;
		TArray<FHitResult> Results;
		UKismetSystemLibrary::SphereTraceMultiForObjects(
			this,
			StartLoc,
			EndLoc,
			SphereSweepRadius,
			ObjectTypes,
			false,
			ActorsToIgnore,
			DrawDebugType,
			Results,
			false,
			FLinearColor::Green,
			FLinearColor::Red,
			5.0f
			);

		for (const FHitResult& HitResult : Results)
		{
			if (HitActors.Contains(HitResult.GetActor()))
			{
				continue;
			}
			HitActors.Add(HitResult.GetActor());
			OutHitResults.Add(HitResult);
		}
	}
	return OutHitResults;
}
