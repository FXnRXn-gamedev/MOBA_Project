// FXnRXn copyright


#include "Animations/MOBA_AnimInstanceBase.h"

#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/KismetMathLibrary.h"

// ---> UNREAL MEMEBERS <---
//---------------------------------------------------------

void UMOBA_AnimInstanceBase::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();

	// Initialize
	OwnerCharacter = Cast<ACharacter>(TryGetPawnOwner());
	if (!IsValid(OwnerCharacter)) return;

	CharacterMovementComp = OwnerCharacter->GetCharacterMovement();
}

void UMOBA_AnimInstanceBase::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);
	
	if (!IsValid(OwnerCharacter)) return;

	Speed = OwnerCharacter->GetVelocity().Length();
	FRotator BodyRot = OwnerCharacter->GetActorRotation();
	FRotator BodyRotDelta = UKismetMathLibrary::NormalizedDeltaRotator(BodyRot, BodyPrevRot);
	BodyPrevRot = BodyRot;
	YawSpeed = BodyRotDelta.Yaw / DeltaSeconds;
	SmoothedYawSpeed = UKismetMathLibrary::FInterpTo(SmoothedYawSpeed, YawSpeed, DeltaSeconds, YawSpeedSmoothLerpSpeed);

	FRotator LookRot = OwnerCharacter->GetBaseAimRotation();
	LookRotOffset = UKismetMathLibrary::NormalizedDeltaRotator(LookRot, BodyRot);

	if (CharacterMovementComp)
	{
		bIsJumping = CharacterMovementComp->IsFalling();
	}
}

void UMOBA_AnimInstanceBase::NativeThreadSafeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeThreadSafeUpdateAnimation(DeltaSeconds);

	
}
