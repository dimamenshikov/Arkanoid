#include "Bonuses/BonusInfinitive/BonusRocket.h"
#include "Arkanoid/Public/World/Block.h"
#include "Kismet/GameplayStatics.h"

void ABonusRocket::StartGame()
{
	Super::StartGame();

	if (Paddle)
	{
		Activate();
	}
}

void ABonusRocket::NotifyActorBeginOverlap(AActor* OtherActor)
{
	IgnoreOtherBonus = true;

	Super::NotifyActorBeginOverlap(OtherActor);

	if (auto Block = Cast<ABlock>(OtherActor); Paddle && Block)
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

void ABonusRocket::Activate()
{
	SetActorEnableCollision(true);
	SetActorHiddenInGame(false);
	BonusMesh->SetCollisionResponseToChannel(ECC_WorldStatic, ECR_Block);

	GetWorldTimerManager().SetTimer(Timer, this, &ABonusRocket::MoveRocket, GetWorld()->DeltaTimeSeconds, true);
}

void ABonusRocket::MoveRocket()
{
	AddActorWorldOffset(FVector(SpeedRocket * GetWorld()->DeltaTimeSeconds, 0.0f, 0.0f), true);
}

void ABonusRocket::BonusTake()
{
	ABonus::BonusTake();
}
