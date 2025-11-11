#pragma once

#include "CoreMinimal.h"
#include "Bonuses/BonusTemporary.h"
#include "BonusManagementInvert.generated.h"

UCLASS(Abstract)
class ARKANOID_API ABonusManagementInvert : public ABonusTemporary
{
	GENERATED_BODY()

protected:
	virtual void Activate() override;
	virtual void DeleteBonus() override;
};
