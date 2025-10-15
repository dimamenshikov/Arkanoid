#pragma once

#include "Arkanoid/Public/Bonuses/Bonus.h"
#include "CoreMinimal.h"
#include "BonusDecreasePaddleSize.generated.h"

UCLASS(Abstract)
class ARKANOID_API ABonusDecreasePaddleSize : public ABonus
{
	GENERATED_BODY()

	//					Parent:

	// Variable

	// Function
public:
	ABonusDecreasePaddleSize();

	//					Gameplay:

	// Variable

	// Function
protected:
	virtual void BonusAction(ABonus* OldBonus) override;
	virtual void UpdateBonus() override;
	virtual void ResetData() override;
};
