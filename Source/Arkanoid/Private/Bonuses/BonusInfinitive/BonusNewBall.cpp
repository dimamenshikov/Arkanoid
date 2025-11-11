#include "Arkanoid/Public/Bonuses/BonusInfinitive/BonusNewBall.h"
#include "Arkanoid/Public/Bonuses/BonusTemporary/BonusMagnet.h"
#include "Arkanoid/Public/Framework/Paddle.h"
#include "Arkanoid/Public/World/Ball.h"
#include "Bonuses/SaveClasses/BonusInfinitive_S.h"
#include "Bonuses/SaveClasses/BonusNewBall_S.h"
#include "Components/ArrowComponent.h"
#include "Framework/ArkanoidGameplayClasses.h"
#include "Framework/ArkanoidPC.h"
#include "Kismet/GameplayStatics.h"

void ABonusNewBall::StartMove()
{
	for (auto& Ball : NewBalls)
	{
		if (Ball && !Ball->bMovement)
		{
			Ball->DetachFromActor(FDetachmentTransformRules::KeepWorldTransform);
			Ball->ActiveMove(true);
			break;
		}
	}
}

void ABonusNewBall::BallDead(AActor* Destroyed)
{
	if (Paddle && Paddle->CurrentBall == Destroyed)
	{
		Paddle->CurrentBall = NewBalls[0];
		NewBalls.RemoveAt(0);

		for (auto Bonus : Paddle->Bonuses)
		{
			if (auto BonusMagnet = Cast<ABonusMagnet>(Bonus))
			{
				Paddle->CurrentBall->OnBallHit.AddDynamic(BonusMagnet, &ABonusMagnet::MagnetBall);
				break;
			}
		}
	}
	else
	{
		NewBalls.Remove(Cast<ABall>(Destroyed));
	}
	if (NewBalls.IsEmpty())
	{
		DeleteBonus();
	}
}

void ABonusNewBall::Update()
{
	if (auto NewBall = GetWorld()->SpawnActor<ABall>(BallClass, Paddle->Arrow->GetComponentLocation(),
	                                                 Paddle->Arrow->GetComponentRotation()); NewBall && Paddle->
		CurrentBall)
	{
		NewBall->AttachToActor(Paddle, FAttachmentTransformRules::KeepWorldTransform);
		NewBall->Init(Paddle);
		NewBall->OnDestroyed.AddDynamic(this, &ABonusNewBall::BallDead);
		NewBalls.Add(NewBall);
	}
}

void ABonusNewBall::Activate()
{
	Paddle->CurrentBall->OnDestroyed.RemoveDynamic(Paddle, &APaddle::BallDead);
	Paddle->CurrentBall->OnDestroyed.AddDynamic(this, &ABonusNewBall::BallDead);
	Paddle->GameplayClasses->ArkanoidPC->OnStartMove.AddDynamic(this, &ABonusNewBall::StartMove);

	if (!bCanUpdate) return;

	Update();
}

void ABonusNewBall::DeleteBonus()
{
	if (Paddle)
	{
		Paddle->CurrentBall->OnDestroyed.AddDynamic(Paddle, &APaddle::BallDead);
	}

	Super::DeleteBonus();
}

USaveGame* ABonusNewBall::Save(USaveGame* BaseSaveObject)
{
	INIT_SAVE_OBJECT(UBonusNewBall_S, BonusNewBall_S);

	for (auto& Ball : NewBalls)
	{
		BonusNewBall_S->Balls.Add(Ball->GetName());
	}
	return Super::Save(BonusNewBall_S);;
}

void ABonusNewBall::FindReferences(const USaveGame*& SaveGameObject, const TMap<FString, AActor*>& ExistActors)
{
	Super::FindReferences(SaveGameObject, ExistActors);
	auto BonusNewBall_S = Cast<UBonusNewBall_S>(SaveGameObject);
	for (auto& BallName : BonusNewBall_S->Balls)
	{
		auto NewBall = Cast<ABall>(ExistActors.FindRef(BallName));
		NewBalls.Add(NewBall);
		NewBall->OnDestroyed.AddDynamic(this, &ABonusNewBall::BallDead);
	}
}

void ABonusNewBall::Load(const USaveGame*& SaveGameObject)
{
	bCanUpdate = false;
	Super::Load(SaveGameObject);
	bCanUpdate = true;
}
