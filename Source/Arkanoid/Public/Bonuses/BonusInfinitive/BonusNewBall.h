#pragma once

#include "CoreMinimal.h"
#include "Bonuses/BonusInfinitive.h"
#include "BonusNewBall.generated.h"

class ABall;

UCLASS(Abstract)
class ARKANOID_API ABonusNewBall : public ABonusInfinitive
{
	GENERATED_BODY()

protected:
	virtual void Update() override;
	virtual void Activate() override;
	virtual void DeleteBonus() override;
	
	virtual USaveGame* Save(USaveGame* BaseSaveObject = nullptr) override;
	virtual void FindReferences(const USaveGame*& SaveGameObject, const TMap<FString, AActor*>& ExistActors) override;
	virtual void Load(const USaveGame*& SaveGameObject) override;

private:
	UFUNCTION()	void StartMove();
	UFUNCTION()	void BallDead(AActor* Destroyed);
	
	UPROPERTY()	TArray<ABall*> NewBalls;
	UPROPERTY(EditDefaultsOnly)	TSubclassOf<ABall> BallClass = nullptr;
	
	bool bCanUpdate = true;
};
