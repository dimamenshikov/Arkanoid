#include "Arkanoid/Public/Bonuses/BonusTemporary/BonusManagementInvert.h"
#include "Arkanoid/Public/Framework/Paddle.h"

void ABonusManagementInvert::Activate()
{
	Paddle->PaddleSpeed *= -1;
}

void ABonusManagementInvert::DeleteBonus()
{
	Activate();

	Super::DeleteBonus();
}
