#pragma once

#include "CoreMinimal.h"
#include "Arkanoid/Public/Bonuses/Bonus.h"
#include "BonusIncreaseLife.generated.h"

UCLASS(Abstract)
class ARKANOID_API ABonusIncreaseLife : public ABonus
{
	GENERATED_BODY()

	//					Parent:

	// Variable

	// Function
public:
	ABonusIncreaseLife();

	//					Gameplay:

	// Variable

	// Function
protected:
	virtual void BonusAction(ABonus* OldBonus) override;
};
