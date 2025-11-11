#include "Arkanoid/Public/Bonuses/BonusInfinitive/BonusIncreasePaddleSize.h"
#include "Arkanoid/Public/Framework/Paddle.h"
#include "Bonuses/BonusInfinitive/BonusDecreasePaddleSize.h"
#include "Components/BoxComponent.h"
#include "Engine/StaticMeshActor.h"
#include "Kismet/GameplayStatics.h"

ABonusIncreasePaddleSize::ABonusIncreasePaddleSize()
{
	Value = 100.0f;
}

void ABonusIncreasePaddleSize::Activate()
{
	float CurrentPaddleSize = (Paddle->StaticMesh->GetComponentScale().Y + 0.4f) * 100;
	float NewSize = FMath::Min(Paddle->GameplaySetting.MaxSizePaddle, CurrentPaddleSize + Value);

	if (NewSize != CurrentPaddleSize)
	{
		const FVector PaddleLocation = Paddle->GetActorLocation();
		FVector PaddleScale = Paddle->StaticMesh->GetComponentScale();
		FVector End = FVector(0.0f, NewSize / 2, 0.0f) + PaddleLocation;
		FHitResult Hit;
		const TArray<AActor*> IgnoreActors{Paddle};
		UKismetSystemLibrary::LineTraceSingle(GetWorld(), PaddleLocation, End, TraceTypeQuery1,
		                                      false, IgnoreActors, EDrawDebugTrace::None, Hit, true);
		if (!Cast<AStaticMeshActor>(Hit.GetActor()))
		{
			End = -1 * End + 2 * PaddleLocation;
			UKismetSystemLibrary::LineTraceSingle(GetWorld(), PaddleLocation, End, TraceTypeQuery1,
			                                      false, IgnoreActors, EDrawDebugTrace::None, Hit, true);
		}
		if (Cast<AStaticMeshActor>(Hit.GetActor()))
		{
			const double Distance = PaddleLocation.Y - Hit.Location.Y;
			Paddle->AddActorLocalOffset(FVector(0.0f, (FMath::Abs(Distance) / Distance)
			                                    * FMath::Abs(NewSize / 2 - FMath::Abs(Distance)), 0.0f));
		}
		PaddleScale.Y = NewSize / 100 - 0.4f;
		Paddle->StaticMesh->SetWorldScale3D(FVector(PaddleScale));
		Paddle->BoxCollisionRoot->SetBoxExtent(FVector(20.0f, NewSize / 2, 25.0f));
	}
}

void ABonusIncreasePaddleSize::DeleteBonus()
{
	FVector PaddleScale = Paddle->StaticMesh->GetComponentScale();
	PaddleScale.Y = Paddle->GameplaySetting.DefaultSizePaddle / 100 - 0.4f;
	Paddle->StaticMesh->SetWorldScale3D(FVector(PaddleScale));
	Paddle->BoxCollisionRoot->SetBoxExtent(FVector(20.0f, Paddle->GameplaySetting.DefaultSizePaddle / 2, 25.0f));

	Super::DeleteBonus();
}

USaveGame* ABonusIncreasePaddleSize::Save(USaveGame* BaseSaveObject)
{
	if (Paddle)
	{
		Value = (Paddle->StaticMesh->GetComponentScale().Y + 0.4f) * 100 - Paddle->GameplaySetting.DefaultSizePaddle;
	}
	return Super::Save(BaseSaveObject);
}

void ABonusIncreasePaddleSize::Load(const USaveGame*& SaveGameObject)
{
	Super::Load(SaveGameObject);
	Value = 100.0f;
}
