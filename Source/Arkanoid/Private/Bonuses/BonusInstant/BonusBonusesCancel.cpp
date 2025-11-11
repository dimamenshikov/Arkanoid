#include "Bonuses/BonusInstant/BonusBonusesCancel.h"
#include "Bonuses/BonusInfinitive.h"
#include "Framework/Paddle.h"

void ABonusBonusesCancel::Activate()
{
	for (int32 i = 0; i < Paddle->Bonuses.Num();)
	{
		Paddle->Bonuses[i]->DeleteBonus();
	}
}
