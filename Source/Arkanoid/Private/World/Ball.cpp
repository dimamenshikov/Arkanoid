#include "Arkanoid/Public/World/Ball.h"
#include "Arkanoid/Public/Framework/Paddle.h"
#include "Arkanoid/Public/Interface/Interaction.h"
#include "Kismet/GameplayStatics.h"
#include "SaveClasses/Ball_S.h"
#include "Interface/SaveAndLoadGame.h"

ABall::ABall()
{
	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Ball"));
	SetRootComponent(StaticMesh);
}

void ABall::StartGame()
{
	ActiveMove(bMovement);
}

void ABall::NotifyHit(UPrimitiveComponent* MyComp, AActor* Other, UPrimitiveComponent* OtherComp, bool bSelfMoved,
                      FVector HitLocation, FVector HitNormal, FVector NormalImpulse, const FHitResult& Hit)
{
	if (CanSoundHit)
	{
		CanSoundHit = false;
		UGameplayStatics::PlaySound2D(this, SoundHit);
		auto CanSound = [this]()-> void
		{
			CanSoundHit = true;
		};
		FTimerHandle T;
		GetWorldTimerManager().SetTimer(T, CanSound, 0.2f, false);
	}
	NextDirection -= 2 * Hit.Normal * FVector::DotProduct(CurrentDirection, Hit.Normal);

	if (const auto Obstacle = Cast<IInteraction>(Other))
	{
		Obstacle->Interaction(this, Hit);
	}
	OnBallHit.Broadcast(Hit);
}

void ABall::ActiveMove(const bool Active)
{
	bMovement = Active;
	if (bMovement)
	{
		GetWorldTimerManager().SetTimer(Timer, this, &ABall::Move, GetWorld()->DeltaTimeSeconds, true);
	}
	else
	{
		GetWorldTimerManager().ClearTimer(Timer);
	}
}

void ABall::Init(APaddle* OwnerPaddle)
{
	Speed = OwnerPaddle->GameplaySetting.DefaultBallSpeed;
	Power = OwnerPaddle->GameplaySetting.DefaultPower;
	NextDirection = GetActorForwardVector();
}

void ABall::Move()
{
	NextDirection.Z = 0.0f;
	NextDirection.X = FMath::Abs(NextDirection.X) / NextDirection.X * FMath::Max(0.3f, FMath::Abs(NextDirection.X));
	NextDirection.Normalize();
	AddActorWorldRotation(FRotator(0.0f, 1000.0f * GetWorld()->DeltaTimeSeconds, 0.0f));
	PreviousLocation = GetActorLocation();
	NextLocation = PreviousLocation + NextDirection * Speed * GetWorld()->DeltaTimeSeconds;
	SetActorLocation(NextLocation, true);
	CurrentDirection = NextDirection;
}

USaveGame* ABall::Save(USaveGame* BaseSaveObject)
{
	INIT_SAVE_OBJECT(UBall_S, Ball_S);
	SET_VAL_7(Ball_S, bMovement, Speed, Power, NextDirection, NextLocation, PreviousLocation, CurrentDirection, SAVE);
	Ball_S->StaticMesh = StaticMesh->GetStaticMesh();
	Ball_S->Material = StaticMesh->GetMaterial(0);
	Ball_S->Scale = GetActorScale3D();
	if (auto Paddle = GetAttachParentActor())
	{
		Ball_S->AttachOwner = Paddle->GetName();
	}
	return ISaveAndLoadGame::Save(Ball_S);
}

void ABall::FindReferences(const USaveGame*& SaveGameObject, const TMap<FString, AActor*>& ExistActors)
{
	ISaveAndLoadGame::FindReferences(SaveGameObject, ExistActors);
	auto Ball_S = Cast<UBall_S>(SaveGameObject);
	if (auto Paddle = ExistActors.FindRef(Ball_S->AttachOwner))
	{
		AttachToActor(Paddle, FAttachmentTransformRules::KeepWorldTransform);
	}
}

void ABall::Load(const USaveGame*& SaveGameObject)
{
	auto Ball_S = Cast<UBall_S>(SaveGameObject);
	SET_VAL_7(Ball_S, bMovement, Speed, Power, NextDirection, NextLocation, PreviousLocation, CurrentDirection, LOAD);
	StaticMesh->SetStaticMesh(Ball_S->StaticMesh);
	StaticMesh->SetMaterial(0, Ball_S->Material);
	SetActorScale3D(Ball_S->Scale);
}
