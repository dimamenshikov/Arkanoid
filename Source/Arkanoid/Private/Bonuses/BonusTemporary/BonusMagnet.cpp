#include "Arkanoid/Public/Bonuses/BonusTemporary/BonusMagnet.h"
#include "Arkanoid/Public/Framework/Paddle.h"
#include "Arkanoid/Public/World/Ball.h"

void ABonusMagnet::MagnetBall(const FHitResult& HitResult)
{
	if (Paddle && Paddle->CurrentBall && Paddle == HitResult.GetActor())
	{
		Paddle->CurrentBall->ActiveMove(false);
		Paddle->CurrentBall->AttachToActor(Paddle, FAttachmentTransformRules::KeepWorldTransform);
	}
}

void ABonusMagnet::Activate()
{
	if (Paddle->CurrentBall)
	{
		Paddle->CurrentBall->OnBallHit.AddDynamic(this, &ABonusMagnet::MagnetBall);
	}
}
