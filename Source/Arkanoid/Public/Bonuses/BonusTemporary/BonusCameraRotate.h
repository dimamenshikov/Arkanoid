#pragma once

#include "CoreMinimal.h"
#include "Arkanoid/Public/Bonuses/Bonus.h"
#include "BonusCameraRotate.generated.h"

UCLASS(Abstract)
class ARKANOID_API ABonusCameraRotate : public ABonus
{
	GENERATED_BODY()
	
	//					Parent:

	// Variable

	// Function
public:
	ABonusCameraRotate();

	//					Gameplay:

	// Variable
private:
	FTimerHandle TimerCameraRotate;
	float CameraSpeed = 30.0f;
	int32 K = 1;

	// Function
protected:
	virtual void BonusAction(ABonus* OldBonus = nullptr) override;
	virtual void ResetData() override;

private:
	void CameraRotate(); // Вращение камеры
};
