// Copyright  a SAO dreamer


#include "Player/AsunaPlayerController.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"

AAsunaPlayerController::AAsunaPlayerController()
{
	bReplicates = true;
}

void AAsunaPlayerController::BeginPlay()
{
	Super::BeginPlay();
	UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer());
	if (Subsystem)
	{
		Subsystem->AddMappingContext(PlayerContext,0);
		
		bShowMouseCursor = true;
		DefaultMouseCursor = EMouseCursor::Default;

		FInputModeGameAndUI PlayerInputData;
		PlayerInputData.SetHideCursorDuringCapture(false);
		PlayerInputData.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);
		SetInputMode(PlayerInputData);
	}
}

void AAsunaPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();
	if (InputComponent)
	{
		UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(InputComponent);
		if (EnhancedInputComponent)
		{
			EnhancedInputComponent->BindAction(MoveAction,ETriggerEvent::Triggered,this,&AAsunaPlayerController::Move);
		}
	}
}

void AAsunaPlayerController::Move(const FInputActionValue& InputActionValue)
{
	const FVector2D InputAxisVector = InputActionValue.Get<FVector2D>();
	const FRotator Rotation = GetControlRotation();
	const FRotator YawRotation(0.f, Rotation.Yaw, 0.f);

	const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
	const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

	if (APawn* ControlledPawn = GetPawn<APawn>())
	{
		ControlledPawn->AddMovementInput(ForwardDirection, InputAxisVector.Y);
		ControlledPawn->AddMovementInput(RightDirection, InputAxisVector.X);
	}
}
