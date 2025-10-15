#include "Arkanoid/Public/World/Ball.h"
#include "Arkanoid/Public/Framework/Paddle.h"
#include "Arkanoid/Public/Interface/Interaction.h"
#include "Kismet/GameplayStatics.h"

//					Parent:

ABall::ABall()
{
	PrimaryActorTick.bCanEverTick = true;

	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Ball"));
	SetRootComponent(StaticMesh);
}

void ABall::Tick(const float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	if (bMovement)
	{
		Move(DeltaSeconds);
	}
}

void ABall::NotifyHit(UPrimitiveComponent* MyComp, AActor* Other, UPrimitiveComponent* OtherComp, bool bSelfMoved,
					  FVector HitLocation, FVector HitNormal, FVector NormalImpulse, const FHitResult& Hit)
{
	UGameplayStatics::PlaySound2D(this, SoundHit);

	NextDirection -= 2 * Hit.Normal * FVector::DotProduct(CurrentDirection, Hit.Normal);

	if (const auto Obstacle = Cast<IInteraction>(Other))
	{
		Obstacle->Interaction(this, Hit);
	}
	OnBallHit.Broadcast(Hit);
}

//					Gameplay:

void ABall::Init(APaddle* OwnerPaddle)
{
	Paddle = OwnerPaddle;
	Speed = Paddle->GameplaySetting.DefaultBallSpeed;
	Power = Paddle->GameplaySetting.DefaultPower;
	NextDirection = GetActorForwardVector();
}

void ABall::Move(const float DeltaSeconds)
{
	NextDirection.Z = 0.0f;
	NextDirection.X = FMath::Abs(NextDirection.X) / NextDirection.X * FMath::Max(0.3f, FMath::Abs(NextDirection.X));
	NextDirection.Normalize();
	AddActorWorldRotation(FRotator(0.0f, 1000.0f * DeltaSeconds, 0.0f));
	PreviousLocation = GetActorLocation();
	NextLocation = PreviousLocation + NextDirection * Speed * DeltaSeconds;
	SetActorLocation(NextLocation, true);
	CurrentDirection = NextDirection;
}

