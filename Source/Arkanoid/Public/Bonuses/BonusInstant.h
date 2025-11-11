#pragma once

#include "CoreMinimal.h"
#include "Bonus.h"
#include "BonusInstant.generated.h"

UCLASS(Abstract)
class ARKANOID_API ABonusInstant : public ABonus
{
	GENERATED_BODY()

protected:
	virtual void BonusTake() override;
};
