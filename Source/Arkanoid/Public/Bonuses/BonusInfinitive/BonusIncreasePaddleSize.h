#pragma once

#include "CoreMinimal.h"
#include "Arkanoid/Public/Bonuses/Bonus.h"
#include "BonusIncreasePaddleSize.generated.h"

UCLASS(Abstract)
class ARKANOID_API ABonusIncreasePaddleSize : public ABonus
{
	GENERATED_BODY()

	//					Parent:

	// Variable

	// Function
public:
	ABonusIncreasePaddleSize();

	//					Gameplay:

	// Variable

	// Function
protected:
	virtual void BonusAction(ABonus* OldBonus) override;
	virtual void UpdateBonus() override;
	virtual void ResetData() override;
};
