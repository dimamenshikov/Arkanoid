#pragma once

#include "CoreMinimal.h"
#include "Bonuses/BonusInstant.h"
#include "BonusIncreaseLife.generated.h"

UCLASS(Abstract)
class ARKANOID_API ABonusIncreaseLife : public ABonusInstant
{
	GENERATED_BODY()

protected:
	virtual void Activate() override;
};
