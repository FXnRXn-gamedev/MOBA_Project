// FXnRXn copyright

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "MOBA_AnimInstanceBase.generated.h"

class UCharacterMovementComponent;
class ACharacter;


UCLASS()
class MOBA_PROJECT_API UMOBA_AnimInstanceBase : public UAnimInstance
{
	GENERATED_BODY()

	//------------------------------------------------------------------------------------------------------------------
public:
		virtual void NativeInitializeAnimation() override;
		virtual void NativeUpdateAnimation(float DeltaSeconds) override;
		virtual void NativeThreadSafeUpdateAnimation(float DeltaSeconds) override;

#pragma region Getters
	
		UFUNCTION(BlueprintCallable, Category = "---Moba---|Anim", meta=(BlueprintThreadSafe)) //
		FORCEINLINE float GetSpeed() const { return Speed; }

		UFUNCTION(BlueprintCallable, Category = "---Moba---|Anim", meta=(BlueprintThreadSafe)) //
		FORCEINLINE bool IsMoving() const { return Speed != 0.0f; }

		UFUNCTION(BlueprintCallable, Category = "---Moba---|Anim", meta=(BlueprintThreadSafe)) //
		FORCEINLINE bool IsNotMoving() const { return Speed == 0.0f; }

		UFUNCTION(BlueprintCallable, Category = "---Moba---|Anim", meta=(BlueprintThreadSafe)) //
		FORCEINLINE float GetYawSpeed() const { return YawSpeed; }

		UFUNCTION(BlueprintCallable, Category = "---Moba---|Anim", meta=(BlueprintThreadSafe)) //
		FORCEINLINE float GetSmoothedYawSpeed() const { return SmoothedYawSpeed; }

		UFUNCTION(BlueprintCallable, Category = "---Moba---|Anim", meta=(BlueprintThreadSafe)) //
		FORCEINLINE bool GetIsJumping() const { return bIsJumping; }

		UFUNCTION(BlueprintCallable, Category = "---Moba---|Anim", meta=(BlueprintThreadSafe)) //
		FORCEINLINE bool GetIsOnGround() const { return !bIsJumping; }

		UFUNCTION(BlueprintCallable, Category = "---Moba---|Anim", meta=(BlueprintThreadSafe)) //
		FORCEINLINE float GetLookYawOffset() const { return LookRotOffset.Yaw; }

		UFUNCTION(BlueprintCallable, Category = "---Moba---|Anim", meta=(BlueprintThreadSafe)) //
		FORCEINLINE float GetLookPitchOffset() const { return LookRotOffset.Pitch; }

#pragma endregion

	
	//------------------------------------------------------------------------------------------------------------------
protected:
		UPROPERTY(EditAnywhere, Category = "Moba|Anim")
		float YawSpeedSmoothLerpSpeed = 4.0f;

	//------------------------------------------------------------------------------------------------------------------
private:
		UPROPERTY()
		ACharacter* OwnerCharacter; // For both Player and AI

		UPROPERTY()
		UCharacterMovementComponent* CharacterMovementComp; // For both Player and AI

		float Speed;
		float YawSpeed;
		float SmoothedYawSpeed;
		FRotator BodyPrevRot;
		FRotator LookRotOffset;
	
		bool bIsJumping;

	
};
