// FXnRXn copyright


#include "MOBA_Project/Public/Player/MOBA_PlayerCharacter.h"
#include "Player/MOBA_PlayerCharacter.h"

#include "AbilitySystemComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Player/MOBA_PlayerController.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"


// ---> CONSTRUCTOR <---
//----------------------------------------------
AMOBA_PlayerCharacter::AMOBA_PlayerCharacter()
{
	PrimaryActorTick.bCanEverTick = false;

	GetCapsuleComponent()->InitCapsuleSize(64.0f, 96.0f);

	//bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	//bUseControllerRotationRoll = false;

	// Create Camera Boom
	SpringArm = CreateDefaultSubobject<USpringArmComponent>("SpringArmComponent");
	SpringArm->SetupAttachment(RootComponent);
	SpringArm->SocketOffset = FVector(0.0f, 0.0f, 120.0f);
	SpringArm->TargetArmLength = 800.f;
	SpringArm->bUsePawnControlRotation = true;
	SpringArm->bDoCollisionTest = false;
	SpringArm->bEnableCameraLag = true;
	SpringArm->CameraLagSpeed = 50.0f;

	// Create Follow Camera
	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(SpringArm, USpringArmComponent::SocketName);
	FollowCamera->bUsePawnControlRotation = false;

	
	// Configure character movement
	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->bUseControllerDesiredRotation = false;					
	GetCharacterMovement()->AirControl = 0.35f;
	GetCharacterMovement()->MinAnalogWalkSpeed = 20.0f;
	GetCharacterMovement()->BrakingDecelerationWalking = 800.0f;
	GetCharacterMovement()->MaxAcceleration = 1250.0f;
	GetCharacterMovement()->GravityScale = 1.25f;
	
	// Motion Warping
	MotionWarpingComp = CreateDefaultSubobject<UMotionWarpingComponent>(TEXT("MOTION_WARPING_COMPONENT"));
	
}






// ---> UNREAL MEMEBERS <---
//----------------------------------------------

void AMOBA_PlayerCharacter::PawnClientRestart()
{
	Super::PawnClientRestart();

	AMOBA_PlayerController* OwningPlayerController = GetController<AMOBA_PlayerController>();
	if (IsValid(OwningPlayerController))
	{
		UEnhancedInputLocalPlayerSubsystem* InputSubsystem = OwningPlayerController->GetLocalPlayer()->GetSubsystem<UEnhancedInputLocalPlayerSubsystem>();
		if (IsValid(InputSubsystem) && MobaInputMappingContext)
		{
			InputSubsystem->RemoveMappingContext(MobaInputMappingContext);
			InputSubsystem->AddMappingContext(MobaInputMappingContext, 0);
		}
	}
}

void AMOBA_PlayerCharacter::BeginPlay()
{
	Super::BeginPlay();
	GetCharacterMovement()->MaxWalkSpeed = WalkSpeed;
	GetCharacterMovement()->RotationRate = FRotator(0.0f, TurnRate, 0.0f);
	GetCharacterMovement()->JumpZVelocity = JumpForce;
}

void AMOBA_PlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent);
	if (IsValid(EnhancedInputComponent))
	{
		if (JumpAction)
		{
			EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Triggered, this, &AMOBA_PlayerCharacter::PlayerJump);
		}
		if (LookInputAction)
		{
			EnhancedInputComponent->BindAction(LookInputAction, ETriggerEvent::Triggered, this, &AMOBA_PlayerCharacter::HandleLookInput);
		}
		if (MoveInputAction)
		{
			EnhancedInputComponent->BindAction(MoveInputAction, ETriggerEvent::Triggered, this, &AMOBA_PlayerCharacter::HandleMoveInput);
		}

		for (const TPair<EMOBA_AbilityInputID, UInputAction*>& InputActionPair : GameplayAbilityInputActions)
		{
			EnhancedInputComponent->BindAction(InputActionPair.Value, ETriggerEvent::Triggered, this, &AMOBA_PlayerCharacter::HandleAbilityInput, InputActionPair.Key);
		}
	}
}






// ---> PLAYER DEATH & RESPAWN <---
//----------------------------------------------


void AMOBA_PlayerCharacter::OnDead()
{
	Super::OnDead();
	APlayerController* PlayerController = GetController<APlayerController>();
	if (PlayerController)
	{
		DisableInput(PlayerController);
	}
}

void AMOBA_PlayerCharacter::OnRespawn()
{
	Super::OnRespawn();
	APlayerController* PlayerController = GetController<APlayerController>();
	if (PlayerController)
	{
		EnableInput(PlayerController);
	}
}






// ---> PLAYER LOCOMOTION <---
//----------------------------------------------

void AMOBA_PlayerCharacter::PlayerJump()
{
	Jump();
}

void AMOBA_PlayerCharacter::HandleLookInput(const FInputActionValue& Value)
{
	FVector2D LookAxisVector = Value.Get<FVector2D>();

	if (Controller != nullptr)
	{
		AddControllerYawInput(LookAxisVector.X);
		AddControllerPitchInput(-LookAxisVector.Y);
	}
}

void AMOBA_PlayerCharacter::HandleMoveInput(const FInputActionValue& Value)
{
	FVector2D MovementVector = Value.Get<FVector2D>();
	if (Controller != nullptr)
	{
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
		const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

		AddMovementInput(ForwardDirection, MovementVector.Y);
		AddMovementInput(RightDirection, MovementVector.X);
	}
}

void AMOBA_PlayerCharacter::HandleAbilityInput(const FInputActionValue& Value, EMOBA_AbilityInputID AbilityInputID)
{
	bool bPressed = Value.Get<bool>();
	if (bPressed)
	{
		GetAbilitySystemComponent()->AbilityLocalInputPressed((int32)AbilityInputID);
	}
	else
	{
		GetAbilitySystemComponent()->AbilityLocalInputReleased((int32)AbilityInputID);
	}
}

