// FXnRXn copyright

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystem/MOBA_GameplayAbilityTypes.h"
#include "MOBA_Project/Public/Character/MOBA_CharacterBase.h"
#include "MOBA_PlayerCharacter.generated.h"


struct FInputActionValue;
class UInputAction;
class UInputMappingContext;
class USpringArmComponent;
class UCameraComponent;






UCLASS()
class MOBA_PROJECT_API AMOBA_PlayerCharacter : public AMOBA_CharacterBase
{
	GENERATED_BODY()

	//------------------------------------------------------------------------------------------------------------------
public:
		AMOBA_PlayerCharacter();
		virtual void PawnClientRestart() override;
		virtual void BeginPlay() override;
		virtual void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) override;


	
	//------------------------------------------------------------------------------------------------------------------
protected:

	//------------------------------------------------------------------------------------------------------------------
private:
		void PlayerJump();
		void HandleLookInput(const FInputActionValue& Value);
		void HandleMoveInput(const FInputActionValue& Value);
		void HandleAbilityInput(const FInputActionValue& Value, EMOBA_AbilityInputID AbilityInputID);

	
#pragma region Settings
	
		UPROPERTY(EditDefaultsOnly, Category = "Moba|Settings")
		float WalkSpeed = 450.0f;
	
		UPROPERTY(EditDefaultsOnly, Category = "Moba|Settings")
		float TurnRate = 540.0f;

		UPROPERTY(EditDefaultsOnly, Category = "Moba|Settings")
		float JumpForce = 720.0f;

#pragma endregion
	
#pragma region Camera component

		UPROPERTY(VisibleDefaultsOnly, Category = "Moba|Camera")
		USpringArmComponent* SpringArm;

		UPROPERTY(VisibleDefaultsOnly, Category = "Moba|Camera")
		UCameraComponent* FollowCamera;

#pragma endregion

#pragma region Input
	
		UPROPERTY(EditDefaultsOnly, Category = "Moba|Input")
		UInputMappingContext* MobaInputMappingContext;

		UPROPERTY(EditDefaultsOnly, Category = "Moba|Input")
		TMap<EMOBA_AbilityInputID, UInputAction*> GameplayAbilityInputActions;

		UPROPERTY(EditDefaultsOnly, Category = "Moba|Input|Actions")
		UInputAction* JumpAction;

		UPROPERTY(EditDefaultsOnly, Category = "Moba|Input|Actions")
		UInputAction* LookInputAction;

		UPROPERTY(EditDefaultsOnly, Category = "Moba|Input|Actions")
		UInputAction* MoveInputAction;

#pragma endregion


	
	
};
