#include "Arkanoid/Public/Components/LifeBlock.h"

//					Parent:

ULifeBlock::ULifeBlock()
{
	PrimaryComponentTick.bCanEverTick = false;
}

//					Gameplay:

void ULifeBlock::Damage(const int32 Damage)
{
	Life = FMath::Max(Life - Damage, 0);
}

void ULifeBlock::SetLife(const int32 NewLife)
{
	Life = FMath::Abs(NewLife);
}
