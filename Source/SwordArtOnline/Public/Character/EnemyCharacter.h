// Copyright  a SAO dreamer

#pragma once

#include "CoreMinimal.h"
#include "Character/BaseCharacter.h"
#include "Interaction/EnemyInterface.h"
#include "EnemyCharacter.generated.h"

/**
 * 
 */
UCLASS()
class SWORDARTONLINE_API AEnemyCharacter : public ABaseCharacter, public IEnemyInterface
{
	GENERATED_BODY()
public:
	AEnemyCharacter();
	void HighlightEnemy() override;
	void UnHighlightEnemy() override;
};
