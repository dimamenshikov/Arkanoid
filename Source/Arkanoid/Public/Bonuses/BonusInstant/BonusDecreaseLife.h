#pragma once

#include "CoreMinimal.h"
#include "Bonuses/BonusInstant.h"
#include "BonusDecreaseLife.generated.h"

UCLASS(Abstract)
class ARKANOID_API ABonusDecreaseLife : public ABonusInstant
{
	GENERATED_BODY()

protected:
	virtual void Activate() override;
};

