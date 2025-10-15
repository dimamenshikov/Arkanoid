#pragma once

#include "CoreMinimal.h"
#include "Arkanoid/Public/Bonuses/Bonus.h"
#include "BonusSpawnMinBall.generated.h"

class ABall;

UCLASS(Abstract)
class ARKANOID_API ABonusSpawnMinBall : public ABonus
{
	GENERATED_BODY()

	//					Parent:

	// Variable

	// Function
public:
	ABonusSpawnMinBall();

	//					Gameplay:

	// Variable
private:
	UPROPERTY(EditDefaultsOnly, meta = (AllowPrivateAccess = true))
	TSubclassOf<ABall> Ball = nullptr;

	// Function
protected:
	virtual void BonusAction(ABonus* OldBonus) override;
};
