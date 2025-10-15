#pragma once

#include "CoreMinimal.h"
#include "Arkanoid/Public/Bonuses/Bonus.h"
#include "BonusDecreasePower.generated.h"

UCLASS(Abstract)
class ARKANOID_API ABonusDecreasePower : public ABonus
{
	GENERATED_BODY()

	//					Parent:

	// Variable

	// Function
public:
	ABonusDecreasePower();

	//					Gameplay:

	// Variable

	// Function
protected:
	virtual void BonusAction(ABonus* OldBonus) override;
	virtual void UpdateBonus() override;
	virtual void ResetData() override;
};
