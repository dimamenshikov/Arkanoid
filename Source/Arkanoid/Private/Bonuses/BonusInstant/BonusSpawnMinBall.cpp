#include "Arkanoid/Public/Bonuses/BonusInstant/BonusSpawnMinBall.h"
#include "Arkanoid/Public/Framework/Paddle.h"
#include "Arkanoid/Public/World/Ball.h"

void ABonusSpawnMinBall::Activate()
{
	if (BallClass && Paddle->CurrentBall)
	{
		for (int32 i = -1; i < 2; i += 2)
		{
			if (auto Ball = GetWorld()->SpawnActor<ABall>(BallClass,
			                                              Paddle->CurrentBall->GetActorLocation() + Paddle->CurrentBall
			                                              ->GetActorRightVector() * 50.0f * i,
			                                              Paddle->CurrentBall->GetActorRotation() + FRotator(
				                                              0.0f, 90.0f * i, 0.0f)))
			{
				Ball->Init(Paddle);
				Ball->Speed = 2500.0f;
				Ball->Power = 5;
				Ball->SetActorScale3D(FVector(0.5f, 0.5, 0.5f));
				Ball->SetLifeSpan(10.0f);
				Ball->ActiveMove(true);
			}
		}
	}
}
