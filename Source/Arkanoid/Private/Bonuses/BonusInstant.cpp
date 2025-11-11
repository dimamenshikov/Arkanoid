#include "Bonuses/BonusInstant.h"

void ABonusInstant::BonusTake()
{
	Super::BonusTake();

	Destroy();
}
