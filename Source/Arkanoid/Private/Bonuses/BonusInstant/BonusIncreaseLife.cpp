#include "Arkanoid/Public/Bonuses/BonusInstant/BonusIncreaseLife.h"
#include "Arkanoid/Public/Framework/Paddle.h"
#include "Framework/ArkanoidGameplayClasses.h"
#include "Framework/ArkanoidGI.h"

void ABonusIncreaseLife::Activate()
{
	Paddle->GameplayClasses->ArkanoidGI->AddLives(Value);
}
