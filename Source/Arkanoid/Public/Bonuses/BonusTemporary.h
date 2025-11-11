#pragma once

#include "CoreMinimal.h"
#include "BonusInfinitive.h"
#include "BonusTemporary.generated.h"

UCLASS(Abstract)
class ARKANOID_API ABonusTemporary : public ABonusInfinitive
{
	GENERATED_BODY()

protected:
	virtual void BeginPlay() override;
	
	virtual void StartGame() override;
	
	virtual void BonusTake() override;
	virtual void Update() override;
	
	virtual USaveGame* Save(USaveGame* BaseSaveObject = nullptr) override;
	virtual void Load(const USaveGame*& SaveGameObject) override;
	virtual void FindReferences(const USaveGame*& SaveGameObject, const TMap<FString, AActor*>& ExistActors) override;

	UPROPERTY(EditAnywhere)	float BonusLife = 10.0f;

	float BonusDuration = 10.0f;
	bool UpdateTime = true;

private:
	FTimerHandle TimerBonusLife;
};
