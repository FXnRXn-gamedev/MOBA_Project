// FXnRXn copyright

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "AbilitySystemInterface.h"
#include "GenericTeamAgentInterface.h"
#include "GameplayTagContainer.h"


#include "MOBA_CharacterBase.generated.h"


class UAttributeSet;
class UMOBA_AbilitySystemComponent;
class UWidgetComponent;


UCLASS()
class MOBA_PROJECT_API AMOBA_CharacterBase : public ACharacter, public IAbilitySystemInterface, public IGenericTeamAgentInterface
{
	GENERATED_BODY()

	//------------------------------------------------------------------------------------------------------------------
public:
	AMOBA_CharacterBase();
	virtual void BeginPlay() override;
	
	void ServerSideInit();
	void ClientSideInit();
	// Only call In Server(for AI)
	virtual void PossessedBy(AController* NewController) override;
	bool IsLocallyControlledByPlayer() const;
	virtual void GetLifetimeReplicatedProps(TArray<class FLifetimeProperty>& OutLifetimeProps) const override;

	//------------------------------------------------------------------------------------------------------------------
	//--->										GAMEPLAY ABILITY													<---
	//------------------------------------------------------------------------------------------------------------------
	
public:
	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;
	UAttributeSet* GetAttributeSet() const{return AttributeSet;}

private:
	void BindGASChangeDelegates();
	void OnDeathTagUpdated(const FGameplayTag Tag, int32 NewCount);
	
	UPROPERTY(VisibleAnywhere, Category = "Moba|AbilitySystem")
	TObjectPtr<UMOBA_AbilitySystemComponent> AbilitySystemComp;
	
	UPROPERTY()
	TObjectPtr<UAttributeSet> AttributeSet;
	


	//------------------------------------------------------------------------------------------------------------------
	//--->										UI																	<---
	//------------------------------------------------------------------------------------------------------------------

private:
	UPROPERTY(VisibleDefaultsOnly, Category = "Moba|Widget")
	UWidgetComponent* OverHeadWidgetComponent;
	
	void ConfigureOverHeadWidget();

	UPROPERTY(EditDefaultsOnly, Category = "Moba|Widget|OverHeadWidget")
	float OverHeadWidgetVisibilityTimerUpdate = 1.0f;

	UPROPERTY(EditDefaultsOnly, Category = "Moba|Widget|OverHeadWidget")
	float OverHeadWidgetVisibilitySquaredRange = 10000000.0f;

	FTimerHandle OverHeadVisibilityWidgetTimerHandle;
	void UpdateOverHeadVisibilityWidget();
	void SetStatWidgetEnabled(bool bIsEnabled);

	//------------------------------------------------------------------------------------------------------------------
	//--->										DEATH & RESPAWN													    <---
	//------------------------------------------------------------------------------------------------------------------
	
	UPROPERTY(EditDefaultsOnly, Category = "Moba|Death & Respawn")
	float DeathMontageFinishTimeShift = -0.8f;
	
	UPROPERTY(EditDefaultsOnly, Category = "Moba|Death & Respawn")
	UAnimMontage* DeathMontage;
	
	FTimerHandle DeathMontageTimerHandle;
	FTransform MeshRelativeTransform;
	
	void DeathMontageFinished();
	void PlayDeathMontage();
	void StartDeathSequence();
	void Respawn();
	
	// Ragdoll
	void SetRagdollEnabled(bool bIsEnabled);

protected:
	virtual void OnDead();
	virtual void OnRespawn();
	
	
	//------------------------------------------------------------------------------------------------------------------
	//--->										TEAM ID																<---
	//------------------------------------------------------------------------------------------------------------------
	
public:
	// Assign Team Agent to given TeamID
	virtual void SetGenericTeamId(const FGenericTeamId& NewTeamID) override;
	// Retrive TeamID
	virtual FGenericTeamId GetGenericTeamId() const override;
	
private:
	UPROPERTY(Replicated)
	FGenericTeamId TeamID;
	
	
	
	
};
