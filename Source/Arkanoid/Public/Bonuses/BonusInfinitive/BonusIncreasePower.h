#pragma once

#include "CoreMinimal.h"
#include "Bonuses/BonusInfinitive.h"
#include "BonusIncreasePower.generated.h"

UCLASS(Abstract)
class ARKANOID_API ABonusIncreasePower : public ABonusInfinitive
{
	GENERATED_BODY()

public:
	ABonusIncreasePower();

protected:
	virtual void Activate() override;
	virtual void DeleteBonus() override;
};
