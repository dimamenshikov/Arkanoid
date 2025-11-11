#include "Arkanoid/Public/Bonuses/BonusInfinitive/BonusDecreasePaddleSize.h"
#include "Arkanoid/Public/Framework/Paddle.h"
#include "Components/BoxComponent.h"

ABonusDecreasePaddleSize::ABonusDecreasePaddleSize()
{
	Value = 50.0f;
}

void ABonusDecreasePaddleSize::Activate()
{
	float CurrentPaddleSize = (Paddle->StaticMesh->GetComponentScale().Y + 0.4f) * 100;
	float NewSize = FMath::Max(Paddle->GameplaySetting.MinSizePaddle, CurrentPaddleSize - Value);

	if (NewSize != CurrentPaddleSize)
	{
		FVector PaddleScale = Paddle->StaticMesh->GetComponentScale();
		PaddleScale.Y = NewSize / 100 - 0.4f;
		Paddle->StaticMesh->SetWorldScale3D(FVector(PaddleScale));
		Paddle->BoxCollisionRoot->SetBoxExtent(FVector(20.0f, NewSize / 2, 25.0f));
	}
}

void ABonusDecreasePaddleSize::DeleteBonus()
{
	FVector PaddleScale = Paddle->StaticMesh->GetComponentScale();
	PaddleScale.Y = Paddle->GameplaySetting.DefaultSizePaddle / 100 - 0.4f;
	Paddle->StaticMesh->SetWorldScale3D(FVector(PaddleScale));
	Paddle->BoxCollisionRoot->SetBoxExtent(FVector(20.0f, Paddle->GameplaySetting.DefaultSizePaddle / 2, 25.0f));

	Super::DeleteBonus();
}

USaveGame* ABonusDecreasePaddleSize::Save(USaveGame* BaseSaveObject)
{
	if (Paddle)
	{
		Value = Paddle->GameplaySetting.DefaultSizePaddle - (Paddle->StaticMesh->GetComponentScale().Y + 0.4f) * 100;
	}
	return Super::Save(BaseSaveObject);
}

void ABonusDecreasePaddleSize::Load(const USaveGame*& SaveGameObject)
{
	Super::Load(SaveGameObject);
	Value = 50.0f;
}
