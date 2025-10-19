// Copyright a SAO dreamer

#include "Character/BaseCharacter.h"

ABaseCharacter::ABaseCharacter()
{
	PrimaryActorTick.bCanEverTick = false;

	WeaponMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Weapon"));
	WeaponMesh->SetupAttachment(GetMesh(),TEXT("WeaponHandSocket"));
	WeaponMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
}

void ABaseCharacter::BeginPlay()
{
	Super::BeginPlay(); 
}