// Copyright  a SAO dreamer

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "AsunaPlayerController.generated.h"

struct FInputActionValue;
class UInputAction;
class UInputMappingContext;
class IEnemyInterface;
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
	void PlayerTick(float DeltaTime) override;
private:
	UPROPERTY(EditAnywhere,Category=Input)
	TObjectPtr<UInputMappingContext> PlayerContext;
	UPROPERTY(EditAnywhere,Category=Input)
	TObjectPtr<UInputAction> MoveAction;

	//鼠标高亮显示
	IEnemyInterface* LastEnemy;
	IEnemyInterface* CurrentEnemy;
	void CuroseTrace();
	//按键回调函数
	void Move(const FInputActionValue& InputActionValue);
	
};
