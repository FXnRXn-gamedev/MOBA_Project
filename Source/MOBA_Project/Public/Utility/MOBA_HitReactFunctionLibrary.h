// FXnRXn copyright

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "MOBA_HitReactFunctionLibrary.generated.h"

UENUM(BlueprintType)
enum EHitReactDirection : uint8
{
	left 		UMETA(DisplayName = "Left"),
	right 		UMETA(DisplayName = "Right"),
	forward 	UMETA(DisplayName = "Forward"),
	back 		UMETA(DisplayName = "Back")
};


UCLASS()
class MOBA_PROJECT_API UMOBA_HitReactFunctionLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

	//------------------------------------------------------------------------------------------------------------------
public:
	UFUNCTION(BlueprintCallable, Category = "---Moba---|Utility")
	static EHitReactDirection GetHitReactDirection(const FVector& TargetForward, const FVector& ToInstigator);

	UFUNCTION(BlueprintCallable, Category = "---Moba---|Utility")
	static FName GetHitReactDirectionName(const EHitReactDirection& Direction);
};
