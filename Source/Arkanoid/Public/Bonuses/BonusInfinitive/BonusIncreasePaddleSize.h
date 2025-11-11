#pragma once

#include "CoreMinimal.h"
#include "Bonuses/BonusInfinitive.h"
#include "BonusIncreasePaddleSize.generated.h"

UCLASS(Abstract)
class ARKANOID_API ABonusIncreasePaddleSize : public ABonusInfinitive
{
	GENERATED_BODY()

public:
	ABonusIncreasePaddleSize();

protected:
	virtual void Activate() override;
	virtual void DeleteBonus() override;
	
	virtual USaveGame* Save(USaveGame* BaseSaveObject = nullptr) override;
	virtual void Load(const USaveGame*& SaveGameObject) override;
};
