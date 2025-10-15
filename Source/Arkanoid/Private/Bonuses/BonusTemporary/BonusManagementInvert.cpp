#include "Arkanoid/Public/Bonuses/BonusTemporary/BonusManagementInvert.h"
#include "Arkanoid/Public/Framework/Paddle.h"

//					Parent:

ABonusManagementInvert::ABonusManagementInvert()
{
	TypeBonusByTime = TemporaryByTime;
}

//					Gameplay:

void ABonusManagementInvert::BonusAction(ABonus* OldBonus)
{
	Super::BonusAction();

	Paddle->PaddleSpeed *= -1;
}

void ABonusManagementInvert::ResetData()
{
	if (Paddle)
	{
		Paddle->PaddleSpeed *= -1;
	}

	Super::ResetData();
}
