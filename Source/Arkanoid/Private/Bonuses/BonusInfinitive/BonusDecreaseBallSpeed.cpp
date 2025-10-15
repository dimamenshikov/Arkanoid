#include "Arkanoid/Public/Bonuses/BonusInfinitive/BonusDecreaseBallSpeed.h"
#include "Arkanoid/Public/Framework/Paddle.h"
#include "Arkanoid/Public/World/Ball.h"

//					Parent:

ABonusDecreaseBallSpeed::ABonusDecreaseBallSpeed()
{
	Value = 300.0f;
}

//					Gameplay:

void ABonusDecreaseBallSpeed::BonusAction(ABonus* OldBonus)
{
	Super::BonusAction();

	UpdateBonus();
}

void ABonusDecreaseBallSpeed::UpdateBonus()
{
	Super::UpdateBonus();

	if (Paddle && Paddle->CurrentBall && Paddle->CurrentBall->Speed - Value > Paddle->GameplaySetting.MinBallSpeed)
	{
		Paddle->CurrentBall->Speed -= Value;
	}
}

void ABonusDecreaseBallSpeed::ResetData()
{
	if (Paddle && Paddle->CurrentBall)
	{
		Paddle->CurrentBall->Speed = Paddle->GameplaySetting.DefaultBallSpeed;
	}

	Super::ResetData();
}
