#include "Arkanoid/Public/Bonuses/BonusInfinitive/BonusIncreaseBallSpeed.h"
#include "Arkanoid/Public/Framework/Paddle.h"
#include "Arkanoid/Public/World/Ball.h"
#include "Bonuses/BonusInfinitive/BonusDecreaseBallSpeed.h"
#include "Framework/ArkanoidGameplayClasses.h"
#include "Framework/ArkanoidGI.h"

ABonusIncreaseBallSpeed::ABonusIncreaseBallSpeed()
{
	Value = 300.0f;
}

void ABonusIncreaseBallSpeed::Activate()
{
	if (Paddle->CurrentBall && Paddle->GameplayClasses->ArkanoidGI->LevelLoad)
	{
		Paddle->CurrentBall->Speed = FMath::Min(Paddle->GameplaySetting.MaxBallSpeed,
		                                        Paddle->CurrentBall->Speed + Value);
	}
}

void ABonusIncreaseBallSpeed::DeleteBonus()
{
	if (Paddle && Paddle->CurrentBall)
	{
		Paddle->CurrentBall->Speed = Paddle->GameplaySetting.DefaultBallSpeed;
	}

	Super::DeleteBonus();
}
