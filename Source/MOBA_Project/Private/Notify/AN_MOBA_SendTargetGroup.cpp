// FXnRXn copyright


#include "Notify/AN_MOBA_SendTargetGroup.h"

#include "AbilitySystemBlueprintLibrary.h"

void UAN_MOBA_SendTargetGroup::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation,
                                      const FAnimNotifyEventReference& EventReference)
{
	Super::Notify(MeshComp, Animation, EventReference);

	if (!MeshComp && !MeshComp->GetOwner()) return;
	if (TargetSocketName.Num() <= 1) return;
	if (!UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(MeshComp->GetOwner())) return;

	FGameplayEventData Data;
	for (int i = 1; i < TargetSocketName.Num(); ++i)
	{
		// Heap Location
		FGameplayAbilityTargetData_LocationInfo* LocationInfo = new FGameplayAbilityTargetData_LocationInfo();

		FVector StartLoc = MeshComp->GetSocketLocation(TargetSocketName[i-1]);
		FVector EndLoc = MeshComp->GetSocketLocation(TargetSocketName[i]);

		LocationInfo->SourceLocation.LiteralTransform.SetLocation(StartLoc);
		LocationInfo->TargetLocation.LiteralTransform.SetLocation(EndLoc);

		Data.TargetData.Add(LocationInfo);
	}
	
	UAbilitySystemBlueprintLibrary::SendGameplayEventToActor(MeshComp->GetOwner(), TargetGroupTag, Data);
}
