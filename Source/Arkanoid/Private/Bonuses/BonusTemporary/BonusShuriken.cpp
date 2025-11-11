#include "Arkanoid/Public/Bonuses/BonusTemporary/BonusShuriken.h"
#include "Arkanoid/Public/Framework/Paddle.h"
#include "Arkanoid/Public/World/Ball.h"
#include "Arkanoid/Public/World/Block.h"
#include "Bonuses/SaveClasses/BonusShuriken_S.h"
#include "Kismet/GameplayStatics.h"

void ABonusShuriken::Shuriken(const FHitResult& HitResult)
{
	if (auto Block = Cast<ABlock>(HitResult.GetActor()))
	{
		Block->Exterminate();
	}
	if (!HitResult.GetActor())
	{
		Paddle->CurrentBall->NextDirection = Paddle->CurrentBall->CurrentDirection;
		Paddle->CurrentBall->SetActorLocation(Paddle->CurrentBall->NextLocation);
	}
}

void ABonusShuriken::Activate()
{
	if (Paddle->CurrentBall)
	{
		Paddle->CurrentBall->OnBallHit.AddDynamic(this, &ABonusShuriken::Shuriken);
		OldScale = Paddle->CurrentBall->GetActorScale3D();
		OldStaticMesh = Paddle->CurrentBall->StaticMesh->GetStaticMesh();
		OldMaterial = Paddle->CurrentBall->StaticMesh->GetMaterial(0);
		Paddle->CurrentBall->StaticMesh->SetStaticMesh(BonusMesh->GetStaticMesh());
		Paddle->CurrentBall->StaticMesh->SetMaterial(0, BonusMesh->GetMaterial(0));
		Paddle->CurrentBall->SetActorScale3D(FVector(0.2f));
	}
}

void ABonusShuriken::DeleteBonus()
{
	if (Paddle->CurrentBall)
	{
		Paddle->CurrentBall->SetActorScale3D(OldScale);
		Paddle->CurrentBall->StaticMesh->SetStaticMesh(OldStaticMesh);
		Paddle->CurrentBall->StaticMesh->SetMaterial(0, OldMaterial);
	}

	Super::DeleteBonus();
}

USaveGame* ABonusShuriken::Save(USaveGame* BaseSaveObject)
{
	INIT_SAVE_OBJECT(UBonusShuriken_S, BonusShuriken_S);
	SET_VAL_3(BonusShuriken_S, OldStaticMesh, OldMaterial, OldScale, SAVE);
	return Super::Save(BonusShuriken_S);
}

void ABonusShuriken::FindReferences(const USaveGame*& SaveGameObject, const TMap<FString, AActor*>& ExistActors)
{
	Super::FindReferences(SaveGameObject, ExistActors);
}

void ABonusShuriken::Load(const USaveGame*& SaveGameObject)
{
	Super::Load(SaveGameObject);
	auto BonusShuriken_S = Cast<UBonusShuriken_S>(SaveGameObject);
	SET_VAL_3(BonusShuriken_S, OldStaticMesh, OldMaterial, OldScale, LOAD);
}
