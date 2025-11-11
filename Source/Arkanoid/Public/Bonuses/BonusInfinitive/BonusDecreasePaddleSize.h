#pragma once

#include "CoreMinimal.h"
#include "Bonuses/BonusInfinitive.h"
#include "BonusDecreasePaddleSize.generated.h"

UCLASS(Abstract)
class ARKANOID_API ABonusDecreasePaddleSize : public ABonusInfinitive
{
	GENERATED_BODY()

public:
	ABonusDecreasePaddleSize();

protected:
	virtual void Activate() override;
	virtual void DeleteBonus() override;
	
	virtual USaveGame* Save(USaveGame* BaseSaveObject = nullptr) override;
	virtual void Load(const USaveGame*& SaveGameObject) override;
};
