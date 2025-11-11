#include "Arkanoid/Public/Bonuses/BonusTemporary/BonusNewPaddle.h"
#include "Arkanoid/Public/Framework/Paddle.h"
#include "Engine/StaticMeshActor.h"

void ABonusNewPaddle::NotifyHit(UPrimitiveComponent* MyComp, AActor* Other, UPrimitiveComponent* OtherComp,
                                bool bSelfMoved, FVector HitLocation, FVector HitNormal, FVector NormalImpulse,
                                const FHitResult& Hit)
{
	if (Cast<AStaticMeshActor>(Other))
	{
		Speed *= -1;
	}
}

void ABonusNewPaddle::Update()
{
	Super::Update();

	if (LoadingComplete && Paddle)
	{
		LoadingComplete = false;
		GetWorldTimerManager().SetTimer(Timer, this, &ABonusNewPaddle::MovePaddle, GetWorld()->DeltaTimeSeconds, true);
	}
}

void ABonusNewPaddle::MovePaddle()
{
	AddActorLocalOffset(FVector(0.0f, Speed * GetWorld()->DeltaTimeSeconds, 0.0f), true);
}

void ABonusNewPaddle::Activate()
{
	SetActorHiddenInGame(false);
	SetActorEnableCollision(true);

	BonusMesh->SetCollisionProfileName("BlockAll");

	SetActorScale3D(FVector(0.4f, 3.0f, 0.4f));

	if (!Loading)
	{
		SetActorLocation(Paddle->GetActorLocation() - FVector(110.0f, 0.0f, 0.0f));
		GetWorldTimerManager().SetTimer(Timer, this, &ABonusNewPaddle::MovePaddle, GetWorld()->DeltaTimeSeconds, true);
	}
}

void ABonusNewPaddle::Load(const USaveGame*& SaveGameObject)
{
	Loading = true;
	Super::Load(SaveGameObject);
	Loading = false;
}
