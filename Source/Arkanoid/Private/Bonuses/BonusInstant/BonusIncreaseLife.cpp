#include "Arkanoid/Public/Bonuses/BonusInstant/BonusIncreaseLife.h"
#include "Arkanoid/Public/Framework/Paddle.h"

//					Parent:

ABonusIncreaseLife::ABonusIncreaseLife()
{
	TypeBonusByTime = Instant;
	Value = 1.0f;
}

//					Gameplay:

void ABonusIncreaseLife::BonusAction(ABonus* OldBonus)
{
	Super::BonusAction();

	Paddle->SetLives(Value);
}
