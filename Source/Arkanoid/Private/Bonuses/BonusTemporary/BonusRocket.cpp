#include "Arkanoid/Public/Bonuses/BonusTemporary/BonusRocket.h"
#include "Arkanoid/Public/World/Block.h"
#include "Kismet/GameplayStatics.h"

//					Parent:

ABonusRocket::ABonusRocket()
{
	TypeBonusByTime = TemporaryByCondition;
}

void ABonusRocket::NotifyActorBeginOverlap(AActor* OtherActor)
{
	Super::NotifyActorBeginOverlap(OtherActor);

	if (auto Block = Cast<ABlock>(OtherActor); bInteractionPaddle && Block)
	{
		Block->Exterminate();
	}
}

void ABonusRocket::NotifyHit(class UPrimitiveComponent* MyComp, AActor* Other, class UPrimitiveComponent* OtherComp,
                             bool bSelfMoved, FVector HitLocation, FVector HitNormal, FVector NormalImpulse,
                             const FHitResult& Hit)
{
	Super::NotifyHit(MyComp, Other, OtherComp, bSelfMoved, HitLocation, HitNormal, NormalImpulse, Hit);

	UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), EffectDestroy, GetActorTransform());
	Destroy();
}

//					Gameplay:

void ABonusRocket::BonusAction(ABonus* OldBonus)
{
	Super::BonusAction();

	SetActorScale3D(FVector(0.25f));
	BonusMesh->SetMaterial(0, RocketMaterial);
	BonusMesh->SetStaticMesh(RocketMesh);
	SetActorEnableCollision(true);
	SetActorHiddenInGame(false);
	BonusMesh->SetCollisionResponseToChannel(ECC_WorldStatic, ECR_Block);
	GetWorldTimerManager().SetTimer(Timer, this, &ABonusRocket::MoveRocket, 0.033333f, true);
}

void ABonusRocket::MoveRocket()
{
	AddActorWorldOffset(FVector(SpeedShuriken * GetWorld()->GetDeltaSeconds(), 0.0f, 0.0f), true);
}
