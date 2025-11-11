#pragma once

#include "CoreMinimal.h"
#include "Arkanoid/Public/Bonuses/Bonus.h"
#include "Bonuses/BonusInstant.h"
#include "BonusSpawnMinBall.generated.h"

class ABall;

UCLASS(Abstract)
class ARKANOID_API ABonusSpawnMinBall : public ABonusInstant
{
	GENERATED_BODY()

protected:
	virtual void Activate() override;

private:
	UPROPERTY(EditDefaultsOnly)	TSubclassOf<ABall> BallClass = nullptr;
};
