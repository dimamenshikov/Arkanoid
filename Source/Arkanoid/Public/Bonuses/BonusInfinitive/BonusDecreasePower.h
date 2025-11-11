#pragma once

#include "CoreMinimal.h"
#include "Bonuses/BonusInfinitive.h"
#include "BonusDecreasePower.generated.h"

UCLASS(Abstract)
class ARKANOID_API ABonusDecreasePower : public ABonusInfinitive
{
	GENERATED_BODY()

public:
	ABonusDecreasePower();

protected:
	virtual void Activate() override;
	virtual void DeleteBonus() override;
};
