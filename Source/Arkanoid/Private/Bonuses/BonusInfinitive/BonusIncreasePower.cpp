#include "Arkanoid/Public/Bonuses/BonusInfinitive/BonusIncreasePower.h"
#include "Arkanoid/Public/Framework/Paddle.h"
#include "Arkanoid/Public/World/Ball.h"
#include "Bonuses/BonusInfinitive/BonusDecreasePower.h"
#include "Framework/ArkanoidGameplayClasses.h"
#include "Framework/ArkanoidGI.h"

ABonusIncreasePower::ABonusIncreasePower()
{
	Value = 3.0f;
}

void ABonusIncreasePower::Activate()
{
	if (Paddle->CurrentBall && Paddle->GameplayClasses->ArkanoidGI->LevelLoad)
	{
		Paddle->CurrentBall->Power = FMath::Min(Paddle->GameplaySetting.MaxPower, Paddle->CurrentBall->Power + Value);
	}
}

void ABonusIncreasePower::DeleteBonus()
{
	if (Paddle && Paddle->CurrentBall)
	{
		Paddle->CurrentBall->Power = Paddle->GameplaySetting.DefaultPower;
	}

	Super::DeleteBonus();
}
