#include "Arkanoid/Public/Bonuses/BonusTemporary/BonusCameraRotate.h"
#include "Arkanoid/Public/Framework/Paddle.h"
#include "Camera/CameraComponent.h"

//					Parent:

ABonusCameraRotate::ABonusCameraRotate()
{
	TypeBonusByTime = TemporaryByTime;
}

//					Gameplay:

void ABonusCameraRotate::BonusAction(ABonus* OldBonus)
{
	Super::BonusAction();

	const float Time = GetWorld()->GetDeltaSeconds();
	GetWorldTimerManager().SetTimer(TimerCameraRotate, this, &ABonusCameraRotate::CameraRotate, Time, true);
}

void ABonusCameraRotate::ResetData()
{
	if (Paddle && Paddle->Camera)
	{
		Paddle->Camera->SetWorldRotation(FRotator(-90.0f, 0.0f, 0.0f));
		Paddle->CameraRotationYaw = 0.0f;
	}

	Super::ResetData();
}

void ABonusCameraRotate::CameraRotate()
{
	if (Paddle && Paddle->Camera)
	{
		const float Time = GetWorld()->GetDeltaSeconds();
		Paddle->Camera->AddWorldRotation(FRotator(0.0f, Time * CameraSpeed, 0.0f));
		if (Time * CameraSpeed * K + Paddle->CameraRotationYaw > 360.0f)
		{
			Paddle->CameraRotationYaw += Time * CameraSpeed * K - 360;
		}
		else
		{
			Paddle->CameraRotationYaw += Time * CameraSpeed * K;
		}
	}
}
