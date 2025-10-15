#include "Arkanoid/Public/Bonuses/BonusTemporary/BonusMagnet.h"
#include "Arkanoid/Public/Framework/Paddle.h"
#include "Arkanoid/Public/World/Ball.h"

//					Parent:

ABonusMagnet::ABonusMagnet()
{
	TypeBonusByTime = TemporaryByTime;
}

//					Gameplay:

void ABonusMagnet::BonusAction(ABonus* OldBonus)
{
	Super::BonusAction();

	if (Paddle->CurrentBall)
	{
		Paddle->CurrentBall->OnBallHit.AddDynamic(this, &ABonusMagnet::MagnetBall);
	}
}

void ABonusMagnet::MagnetBall(const FHitResult& HitResult)
{
	if (Paddle && Paddle == HitResult.GetActor())
	{
		Paddle->CurrentBall->bMovement = false;
		Paddle->CurrentBall->AttachToActor(Paddle, FAttachmentTransformRules::KeepWorldTransform);
	}
}
