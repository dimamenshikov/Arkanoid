#pragma once

#include "CoreMinimal.h"
#include "Arkanoid/Public/Bonuses/Bonus.h"
#include "BonusNewBall.generated.h"

class ABall;

UCLASS(Abstract)
class ARKANOID_API ABonusNewBall : public ABonus
{
	GENERATED_BODY()

	//					Gameplay:

	// Variable
private:
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<ABall> BallClass = nullptr;
	
	TArray<ABall*> NewBalls;

	// Function
private:
	UFUNCTION()
	void StartMove();
	UFUNCTION()
	void BallDead(AActor* Destroyed);

protected:
	virtual void BonusAction(ABonus* OldBonus) override;
	virtual void UpdateBonus() override;
	virtual void ResetData() override;
};
