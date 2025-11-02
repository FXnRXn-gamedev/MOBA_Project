// FXnRXn copyright


#include "Notify/AN_MOBA_SendGameplayEvent.h"
#include "AbilitySystemBlueprintLibrary.h"
#include "GameplayTagsManager.h"



void UAN_MOBA_SendGameplayEvent::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation,
	const FAnimNotifyEventReference& EventReference)
{
	Super::Notify(MeshComp, Animation, EventReference);

	if (!MeshComp->GetOwner()) return;

	UAbilitySystemComponent* OwnerASC = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(MeshComp->GetOwner());

	if (OwnerASC == nullptr) return;

	UAbilitySystemBlueprintLibrary::SendGameplayEventToActor(MeshComp->GetOwner(), EventTag, FGameplayEventData());
	
}

FString UAN_MOBA_SendGameplayEvent::GetNotifyName_Implementation() const
{
	TArray<FName> TagNames;
	if (EventTag.IsValid())
	{
		UGameplayTagsManager& GameplayTagsManager = UGameplayTagsManager::Get();
		GameplayTagsManager.SplitGameplayTagFName(EventTag, TagNames);
		return TagNames.Last().ToString();
	}
	return FString("None");
}
