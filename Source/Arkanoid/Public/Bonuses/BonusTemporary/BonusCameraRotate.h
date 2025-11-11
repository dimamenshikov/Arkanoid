#pragma once

#include "CoreMinimal.h"
#include "Bonuses/BonusTemporary.h"
#include "BonusCameraRotate.generated.h"

UCLASS(Abstract)
class ARKANOID_API ABonusCameraRotate : public ABonusTemporary
{
	GENERATED_BODY()

protected:
	virtual void Update() override;
	virtual void Activate() override;
	virtual void DeleteBonus() override;

	virtual USaveGame* Save(USaveGame* BaseSaveObject = nullptr) override;
	virtual void Load(const USaveGame*& SaveGameObject) override;
	
private:
	void CameraRotate();
	
	float CameraSpeed = 30.0f;
};
