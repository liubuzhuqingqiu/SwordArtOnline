// Copyright  a SAO dreamer

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "AsunaPlayerController.generated.h"

struct FInputActionValue;
class UInputAction;
class UInputMappingContext;
/**
 * 
 */
UCLASS()
class SWORDARTONLINE_API AAsunaPlayerController : public APlayerController
{
	GENERATED_BODY()
public:
	AAsunaPlayerController();
protected:
	virtual void BeginPlay() override;
	virtual void SetupInputComponent() override;
private:
	UPROPERTY(EditAnywhere,Category=Input)
	TObjectPtr<UInputMappingContext> PlayerContext;
	UPROPERTY(EditAnywhere,Category=Input)
	TObjectPtr<UInputAction> MoveAction;

	void Move(const FInputActionValue& InputActionValue);
};
