#pragma once

#include "CoreMinimal.h"
#include "Bonuses/BonusInfinitive.h"
#include "BonusCannon.generated.h"

class ACannon;

UCLASS(Abstract)
class ARKANOID_API ABonusCannon : public ABonusInfinitive
{
	GENERATED_BODY()

protected:
	virtual void Activate() override;
	virtual void DeleteBonus() override;
	virtual void Update() override;

	virtual USaveGame* Save(USaveGame* BaseSaveObject = nullptr) override;
	virtual void Load(const USaveGame*& SaveGameObject) override;
	
private:
	void Shoot();
	
	UPROPERTY(EditDefaultsOnly)	USoundWave* ShootSound;
	UPROPERTY(EditDefaultsOnly)	TSubclassOf<ACannon> CannonClass;
	
	TArray<ACannon*> Cannons;
	int32 QuantityProjectile = 10;
	bool CanShoot = true;
};
