// Copyright  a SAO dreamer


#include "Character/EnemyCharacter.h"

#include "SwordArtOnline/SwordArtOnline.h"

AEnemyCharacter::AEnemyCharacter()
{
	GetMesh()->SetCollisionResponseToAllChannels(ECR_Block);
	GetMesh()->SetCollisionObjectType(ECC_WorldDynamic);
	GetMesh()->SetCollisionEnabled(ECollisionEnabled::Type::QueryAndPhysics);
}	

void AEnemyCharacter::HighlightEnemy()
{
	GetMesh()->SetRenderCustomDepth(true);
	GetMesh()->SetCustomDepthStencilValue(CUSTOM_DEPTH_RED);
	WeaponMesh->SetRenderCustomDepth(true);
	WeaponMesh->SetCustomDepthStencilValue(CUSTOM_DEPTH_RED);
	
}

void AEnemyCharacter::UnHighlightEnemy()
{
	GetMesh()->SetRenderCustomDepth(false);
	WeaponMesh->SetRenderCustomDepth(false);
}
