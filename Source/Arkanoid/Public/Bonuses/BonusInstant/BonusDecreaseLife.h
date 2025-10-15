#pragma once

#include "CoreMinimal.h"
#include "Arkanoid/Public/Bonuses/Bonus.h"
#include "BonusDecreaseLife.generated.h"

UCLASS(Abstract)
class ARKANOID_API ABonusDecreaseLife : public ABonus
{
	GENERATED_BODY()

	//					Parent:

	// Variable

	// Function
public:
	ABonusDecreaseLife();

	//					Gameplay:

	// Variable

	// Function
protected:
	virtual void BonusAction(ABonus* OldBonus) override;
};

