#pragma once

#include "CoreMinimal.h"
#include "Arkanoid/Public/Bonuses/Bonus.h"
#include "BonusMagnet.generated.h"

class ABall;

UCLASS(Abstract)
class ARKANOID_API ABonusMagnet : public ABonus
{
	GENERATED_BODY()

	//					Parent:

	// Variable

	// Function
public:
	ABonusMagnet();

	//					Gameplay:

	// Variable

	// Function
public:
	UFUNCTION()
	void MagnetBall(const FHitResult& HitResult); // Прикрепление шара к каретки

protected:
	virtual void BonusAction(ABonus* OldBonus) override;
};
