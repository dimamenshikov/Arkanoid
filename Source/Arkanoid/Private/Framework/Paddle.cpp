#include "Arkanoid/Public/Framework/Paddle.h"
#include "Components/ArrowComponent.h"
#include "Components/BoxComponent.h"
#include "Arkanoid/Public/Framework/ArkanoidGameplayClasses.h"
#include "Arkanoid/Public/Framework/ArkanoidGM.h"
#include "Arkanoid/Public/World/Ball.h"
#include "Camera/CameraComponent.h"
#include "Framework/ArkanoidGI.h"
#include "SaveClasses/Paddle_S.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"

APaddle::APaddle()
{
	BoxCollisionRoot = CreateDefaultSubobject<UBoxComponent>(TEXT("Root"));
	SetRootComponent(BoxCollisionRoot);

	GameplaySetting.DefaultSizePaddle = FMath::Max(GameplaySetting.DefaultSizePaddle, 40.0f);
	BoxCollisionRoot->SetBoxExtent(FVector(20.0f, FMath::Abs(GameplaySetting.DefaultSizePaddle / 2), 25.0f));
	BoxCollisionRoot->SetCollisionProfileName("BlockAll");
	BoxCollisionRoot->SetCollisionObjectType(ECC_WorldDynamic);
	BoxCollisionRoot->SetCollisionResponseToChannel(ECC_WorldDynamic, ECR_Overlap);

	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Static MEsh"));
	StaticMesh->SetupAttachment(BoxCollisionRoot);
	StaticMesh->SetCollisionEnabled(ECollisionEnabled::Type::NoCollision);

	LeftStaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("LeftStatic MEsh"));
	LeftStaticMesh->SetupAttachment(StaticMesh);
	LeftStaticMesh->AddRelativeLocation(FVector(0.0f, -50.0f, 0.0f));
	LeftStaticMesh->SetAbsolute(false, false, true);
	LeftStaticMesh->SetCollisionEnabled(ECollisionEnabled::Type::NoCollision);

	RightStaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("RightStatic MEsh"));
	RightStaticMesh->SetupAttachment(StaticMesh);
	RightStaticMesh->AddRelativeLocation(FVector(0.0f, 50.0f, 0.0f));
	RightStaticMesh->SetAbsolute(false, false, true);
	RightStaticMesh->SetCollisionEnabled(ECollisionEnabled::Type::NoCollision);

	Arrow = CreateDefaultSubobject<UArrowComponent>(TEXT("Arrow"));
	Arrow->SetupAttachment(StaticMesh);
	Arrow->AddRelativeLocation(FVector(150.0f, 0.0f, 0.0f));
	Arrow->SetAbsolute(false, false, true);

	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->SetupAttachment(BoxCollisionRoot);
	Camera->SetAbsolute(true, true, true);
}

void APaddle::OnConstruction(const FTransform& Transform)
{
	Super::OnConstruction(Transform);

	GameplaySetting.DefaultSizePaddle = FMath::Max(GameplaySetting.DefaultSizePaddle, 40.0f);
	StaticMesh->SetWorldScale3D(FVector(0.4f, FMath::Max(0, GameplaySetting.DefaultSizePaddle / 100 - 0.4f), 0.5f));
	BoxCollisionRoot->SetBoxExtent(FVector(20.0f, FMath::Abs(GameplaySetting.DefaultSizePaddle / 2), 25.0f));
	const FVector TempScale = FVector(StaticMesh->GetComponentScale().X, StaticMesh->GetComponentScale().X,
	                                  StaticMesh->GetComponentScale().Z);
	LeftStaticMesh->SetWorldScale3D(TempScale);
	RightStaticMesh->SetWorldScale3D(TempScale);
}

void APaddle::BeginPlay()
{
	Super::BeginPlay();

	GameplayClasses->ArkanoidP = this;

	Camera->SetWorldRotation(FRotator(-90.0f, 0.0f, 0.0f));
	Camera->SetWorldLocation(FVector(0.0f, 0.0f, 6000.0f));
	Camera->SetFieldOfView(50.0f);
}

void APaddle::LevelLoad()
{
	SpawnBall();
}

void APaddle::Interaction(ABall* Ball, const FHitResult& HitResult)
{
	const double BallHitLocation = Ball->GetActorLocation().Y;
	const double PaddleCenter = GetActorLocation().Y - (StaticMesh->GetComponentScale().Y * 50 + 20);

	double Alpha = FMath::Clamp((BallHitLocation - PaddleCenter) / (StaticMesh->GetComponentScale().Y * 100 + 40), 0.0f,
	                            1.0f);
	Alpha = (2.0f + 2.0f / 3.0f) * FMath::Pow(Alpha, 3) - 4.0f * FMath::Pow(Alpha, 2) + (2.0f + 1.0f / 3.0f) * Alpha;

	double Rotate = FMath::Lerp(-70.0f, 70.0f, Alpha);

	if (FMath::Abs(Rotate) < 0.25f)
	{
		Rotate = 0.0f;
	}
	Ball->NextDirection = UKismetMathLibrary::Quat_RotateVector(FQuat(FRotator(0.0f, Rotate, 0.0f)),
	                                                            FVector::ForwardVector);
}

void APaddle::SpawnBall()
{
	if (ClassBall && !CurrentBall && GameplayClasses->ArkanoidGI->Lives > 0)
	{
		if (CurrentBall = GetWorld()->SpawnActor<ABall>(ClassBall, Arrow->GetComponentLocation(),
		                                                Arrow->GetComponentRotation()); CurrentBall)
		{
			CurrentBall->OnDestroyed.AddDynamic(this, &APaddle::BallDead);
			CurrentBall->AttachToActor(this, FAttachmentTransformRules::KeepWorldTransform);
			CurrentBall->Init(this);
		}
	}
}

void APaddle::BallDead(AActor* Destroyed)
{
	CurrentBall = nullptr;
	GameplayClasses->ArkanoidGI->AddLives(-1);
	OnLifeChange.Broadcast(GameplayClasses->ArkanoidGI->Lives);

	UGameplayStatics::PlaySound2D(this, SoundBallDeath);
	
	if (GameplayClasses->ArkanoidGI->Lives == 0)
	{
		GameplayClasses->ArkanoidGM->GameEnd(false);
		return;
	}
	
	OnBallDead.Broadcast();
	Bonuses.Empty();
	SpawnBall();
}

USaveGame* APaddle::Save(USaveGame* BaseSaveObject)
{
	INIT_SAVE_OBJECT(UPaddle_S, Paddle_S);
	if (CurrentBall)
	{
		Paddle_S->CurrentBallName = CurrentBall->GetName();
	}
	return Paddle_S;
}

void APaddle::FindReferences(const USaveGame*& SaveGameObject, const TMap<FString, AActor*>& ExistActors)
{
	ISaveAndLoadGame::FindReferences(SaveGameObject, ExistActors);
	auto Paddle_S = Cast<UPaddle_S>(SaveGameObject);
	CurrentBall = Cast<ABall>(ExistActors.FindRef(Paddle_S->CurrentBallName));
	CurrentBall->OnDestroyed.AddDynamic(this, &APaddle::BallDead);
}
