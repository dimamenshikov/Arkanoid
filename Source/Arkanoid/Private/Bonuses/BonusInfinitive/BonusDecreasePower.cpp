#include "Arkanoid/Public/Bonuses/BonusInfinitive/BonusDecreasePower.h"
#include "Arkanoid/Public/Framework/Paddle.h"
#include "Arkanoid/Public/World/Ball.h"
#include "Framework/ArkanoidGameplayClasses.h"
#include "Framework/ArkanoidGI.h"

ABonusDecreasePower::ABonusDecreasePower()
{
	Value = 2.0f;
}

void ABonusDecreasePower::Activate()
{
	if (Paddle->CurrentBall && Paddle->GameplayClasses->ArkanoidGI->LevelLoad)
	{
		Paddle->CurrentBall->Power = FMath::Max(Paddle->GameplaySetting.MinPower, Paddle->CurrentBall->Power - Value);
	}
}

void ABonusDecreasePower::DeleteBonus()
{
	if (Paddle && Paddle->CurrentBall)
	{
		Paddle->CurrentBall->Power = Paddle->GameplaySetting.DefaultPower;
	}

	Super::DeleteBonus();
}
