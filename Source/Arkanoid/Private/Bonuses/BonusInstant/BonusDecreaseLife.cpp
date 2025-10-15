#include "Arkanoid/Public/Bonuses/BonusInstant/BonusDecreaseLife.h"
#include "Arkanoid/Public/Framework/Paddle.h"

//					Parent:

ABonusDecreaseLife::ABonusDecreaseLife()
{
	TypeBonusByTime = Instant;
	Value = 1.0f;
}

//					Gameplay:

void ABonusDecreaseLife::BonusAction(ABonus* OldBonus)
{
	Super::BonusAction();

	Paddle->SetLives(-Value);
}
