#include "Arkanoid/Public/Bonuses/BonusTemporary/BonusShield.h"

//					Parent:
ABonusShield::ABonusShield()
{
	TypeBonusByTime = TemporaryByTime;
}

//					Gameplay:

void ABonusShield::BonusAction(ABonus* OldBonus)
{
	Super::BonusAction();

	SetActorLocation(FVector(-1350.0f, 0.0f, 100.0f));
	SetActorScale3D(FVector(1.0f, 30.0f, 1.0f));
	BonusMesh->SetStaticMesh(ShieldMesh);
	BonusMesh->SetMaterial(0, ShieldMaterial);
	SetActorEnableCollision(true);
	SetActorHiddenInGame(false);
	BonusMesh->SetCollisionProfileName("BlockAllDynamic");
}
