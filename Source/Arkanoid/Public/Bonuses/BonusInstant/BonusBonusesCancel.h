#pragma once

#include "CoreMinimal.h"
#include "Bonuses/BonusInstant.h"
#include "BonusBonusesCancel.generated.h"

UCLASS(Abstract)
class ARKANOID_API ABonusBonusesCancel : public ABonusInstant
{
	GENERATED_BODY()

protected:
	virtual void Activate() override;
};
