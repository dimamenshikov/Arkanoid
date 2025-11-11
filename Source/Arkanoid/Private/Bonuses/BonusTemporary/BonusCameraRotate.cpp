#include "Arkanoid/Public/Bonuses/BonusTemporary/BonusCameraRotate.h"
#include "Arkanoid/Public/Framework/Paddle.h"
#include "Camera/CameraComponent.h"

void ABonusCameraRotate::Update()
{
	Super::Update();

	if (LoadingComplete)
	{
		LoadingComplete = false;
		Activate();
	}
}

void ABonusCameraRotate::CameraRotate()
{
	const float Time = GetWorld()->DeltaTimeSeconds;
	Paddle->Camera->AddWorldRotation(FRotator(0.0f, Time * CameraSpeed, 0.0f));
	if (Time * CameraSpeed + Paddle->CameraRotationYaw > 360.0f)
	{
		Paddle->CameraRotationYaw += Time * CameraSpeed - 360;
	}
	else
	{
		Paddle->CameraRotationYaw += Time * CameraSpeed;
	}
}

void ABonusCameraRotate::Activate()
{
	GetWorldTimerManager().SetTimer(Timer, this, &ABonusCameraRotate::CameraRotate, GetWorld()->DeltaTimeSeconds, true);
}

void ABonusCameraRotate::DeleteBonus()
{
	if (Paddle && Paddle->Camera)
	{
		Paddle->Camera->SetWorldRotation(FRotator(-90.0f, 0.0f, 0.0f));
		Paddle->CameraRotationYaw = 0.0f;
	}

	Super::DeleteBonus();
}

USaveGame* ABonusCameraRotate::Save(USaveGame* BaseSaveObject)
{
	if (Paddle)
	{
		Value = Paddle->CameraRotationYaw;
	}
	return Super::Save(BaseSaveObject);
}

void ABonusCameraRotate::Load(const USaveGame*& SaveGameObject)
{
	Super::Load(SaveGameObject);
	if (Paddle)
	{
		Paddle->CameraRotationYaw = Value;
		Paddle->Camera->SetWorldRotation(FRotator(-90.0f, Value, 0.0f));
	}
}
