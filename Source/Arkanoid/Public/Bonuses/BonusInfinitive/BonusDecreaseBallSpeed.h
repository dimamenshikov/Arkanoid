#pragma once

#include "CoreMinimal.h"
#include "Bonuses/BonusInfinitive.h"
#include "BonusDecreaseBallSpeed.generated.h"

UCLASS(Abstract)
class ARKANOID_API ABonusDecreaseBallSpeed : public ABonusInfinitive
{
	GENERATED_BODY()

public:
	ABonusDecreaseBallSpeed();

protected:
	virtual void Activate() override;
	virtual void DeleteBonus() override;
};
