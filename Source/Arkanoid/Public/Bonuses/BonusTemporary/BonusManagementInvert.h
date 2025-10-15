#pragma once

#include "CoreMinimal.h"
#include "Arkanoid/Public/Bonuses/Bonus.h"
#include "BonusManagementInvert.generated.h"

UCLASS(Abstract)
class ARKANOID_API ABonusManagementInvert : public ABonus
{
	GENERATED_BODY()

public:
	ABonusManagementInvert();

protected:
	virtual void BonusAction(ABonus* OldBonus) override;
	virtual void ResetData() override;
};
