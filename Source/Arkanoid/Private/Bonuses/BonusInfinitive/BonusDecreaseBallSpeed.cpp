#include "Arkanoid/Public/Bonuses/BonusInfinitive/BonusDecreaseBallSpeed.h"
#include "Framework/ArkanoidGameplayClasses.h"
#include "Framework/ArkanoidGI.h"
#include "Framework/Paddle.h"
#include "World/Ball.h"

ABonusDecreaseBallSpeed::ABonusDecreaseBallSpeed()
{
	Value = 300.0f;
}

void ABonusDecreaseBallSpeed::Activate()
{
	if (Paddle->CurrentBall && Paddle->GameplayClasses->ArkanoidGI->LevelLoad)
	{
		Paddle->CurrentBall->Speed = FMath::Max(Paddle->GameplaySetting.MinBallSpeed,
		                                        Paddle->CurrentBall->Speed - Value);
	}
}

void ABonusDecreaseBallSpeed::DeleteBonus()
{
	if (Paddle && Paddle->CurrentBall)
	{
		Paddle->CurrentBall->Speed = Paddle->GameplaySetting.DefaultBallSpeed;
	}

	Super::DeleteBonus();
}
