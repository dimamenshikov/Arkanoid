#pragma once

#include "CoreMinimal.h"
#include "Bonuses/BonusInfinitive.h"
#include "BonusIncreaseBallSpeed.generated.h"

UCLASS(Abstract)
class ARKANOID_API ABonusIncreaseBallSpeed : public ABonusInfinitive
{
	GENERATED_BODY()

public:
	ABonusIncreaseBallSpeed();

protected:
	virtual void Activate() override;
	virtual void DeleteBonus() override;
};
