#include "Arkanoid/Public/Components/LifeBlock.h"

void ULifeBlock::Damage(const int32 Damage)
{
	Life = FMath::Max(Life - Damage, 0);
}

void ULifeBlock::SetLife(const int32 NewLife)
{
	Life = FMath::Abs(NewLife);
}
