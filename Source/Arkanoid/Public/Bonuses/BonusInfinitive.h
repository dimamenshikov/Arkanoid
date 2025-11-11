#pragma once

#include "CoreMinimal.h"
#include "Bonuses/Bonus.h"
#include "Interface/SaveAndLoadGame.h"
#include "BonusInfinitive.generated.h"

UCLASS(Abstract)
class ARKANOID_API ABonusInfinitive : public ABonus
{
	GENERATED_BODY()

public:
	UFUNCTION()	virtual void DeleteBonus();
	
protected:
	virtual void CheckPairedBonuses();
	virtual void Update();
	virtual void BonusTake() override;

	virtual USaveGame* Save(USaveGame* BaseSaveObject = nullptr) override;
	virtual void FindReferences(const USaveGame*& SaveGameObject, const TMap<FString, AActor*>& ExistActors) override;
	virtual void Load(const USaveGame*& SaveGameObject) override;
	
	UPROPERTY(EditDefaultsOnly)	TArray<TSubclassOf<ABonusInfinitive>> PairedBonuses;
	
	bool AutoActivateForLoad = true;
	bool IgnoreOtherBonus = false;
	bool ReplaceOldBonus = false;
};
