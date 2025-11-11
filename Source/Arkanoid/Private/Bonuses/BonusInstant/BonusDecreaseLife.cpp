#include "Arkanoid/Public/Bonuses/BonusInstant/BonusDecreaseLife.h"
#include "Arkanoid/Public/Framework/Paddle.h"
#include "Framework/ArkanoidGameplayClasses.h"
#include "Framework/ArkanoidGI.h"

void ABonusDecreaseLife::Activate()
{
	Paddle->GameplayClasses->ArkanoidGI->AddLives(-Value);
}
