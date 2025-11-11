#pragma once

#include "CoreMinimal.h"
#include "Bonuses/BonusTemporary.h"
#include "BonusMagnet.generated.h"

class ABall;

UCLASS(Abstract)
class ARKANOID_API ABonusMagnet : public ABonusTemporary
{
	GENERATED_BODY()

public:
	UFUNCTION()	void MagnetBall(const FHitResult& HitResult);
	
protected:
	virtual void Activate() override;
};
