// Copyright  a SAO dreamer


#include "Player/AsunaPlayerController.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"
#include "Interaction/EnemyInterface.h"

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

void AAsunaPlayerController::PlayerTick(float DeltaTime)
{
	Super::PlayerTick(DeltaTime);
	CuroseTrace();
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



void AAsunaPlayerController::CuroseTrace()
{
	FHitResult Hitresult;
	GetHitResultUnderCursor(ECC_Visibility,false,Hitresult);

	LastEnemy = CurrentEnemy;
	CurrentEnemy = Cast<IEnemyInterface>(Hitresult.GetActor());

	/**
	 *从鼠标发射射线检测有很多种不同的情况
	 * 情况一：LastEnemy 和 CurrentEnmey都为 null
	 *		- 什么都不做
	 * 情况二：LastEnemy 为 null 但是 CurrentEnemy 不为 null
	 *		- 将 CurrentEnemy 高亮
	 * 情况三：LastEnmey 不为 null 但是 CurrentEnemy 为 null
	 *		- 将LastEnemy 取消高亮
	 * 情况四：两者都不为 null 但是 LastEnemy ！= CurrentEnemy
	 *		- 将 LastEnemy 取消高亮，CurrentEnemy 高亮
	 * 情况五：两者都不为 null 但是 LastEnemy == CurrentEnmey
	 *		- 什么都不做
	 */
	if (LastEnemy == nullptr)
	{
		if (CurrentEnemy == nullptr)
		{
			//情况一：什么都不做
		}else
		{
			//情况二
			CurrentEnemy->HighlightEnemy();
		}
	}
	else
	{
		if (CurrentEnemy == nullptr)
		{
			//情况三
			LastEnemy->UnHighlightEnemy();
		}
		else
		{
			if (LastEnemy != CurrentEnemy)
			{
				//情况四
				LastEnemy->UnHighlightEnemy();
				CurrentEnemy->HighlightEnemy();
			}
			else
			{
				//情况五：什么都不做
			}
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
