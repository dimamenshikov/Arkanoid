#include "Arkanoid/Public/Bonuses/Bonus.h"
#include "Arkanoid/Public/Framework/Paddle.h"
#include "Bonuses/SaveClasses/Bonus_S.h"
#include "Framework/ArkanoidGI.h"
#include "Kismet/GameplayStatics.h"

ABonus::ABonus()
{
	BonusMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BonusMesh"));
	SetRootComponent(BonusMesh);

	BonusMesh->SetCollisionProfileName("OverlapAllDynamic");
}

void ABonus::BeginPlay()
{
	Super::BeginPlay();

	ActiveMove(Cast<UArkanoidGI>(GetGameInstance())->StartGame);
}

void ABonus::StartGame()
{
	ActiveMove(Paddle == nullptr);
}

void ABonus::NotifyActorBeginOverlap(AActor* OtherActor)
{
	Super::NotifyActorBeginOverlap(OtherActor);

	if (Paddle || !Cast<UArkanoidGI>(GetGameInstance())->LevelLoad) return;

	if (Paddle = Cast<APaddle>(OtherActor); Paddle)
	{
		UGameplayStatics::PlaySound2D(this, SoundActivation);
		BonusTake();
	}
}

void ABonus::BonusTake()
{
	ActiveMove(false);

	SetActorEnableCollision(false);
	SetActorHiddenInGame(true);

	Activate();
}

void ABonus::ActiveMove(bool Move)
{
	if (Move)
	{
		GetWorldTimerManager().SetTimer(Timer, this, &ABonus::Move, GetWorld()->DeltaTimeSeconds, true);
	}
	else
	{
		GetWorldTimerManager().ClearTimer(Timer);
	}
}

void ABonus::Move()
{
	AddActorWorldOffset(VectorMove * BonusSpeed * GetWorld()->DeltaTimeSeconds);
}

USaveGame* ABonus::Save(USaveGame* BaseSaveObject)
{
	INIT_SAVE_OBJECT(UBonus_S, Bonus_S);
	Bonus_S->Scale = GetActorScale3D();
	return ISaveAndLoadGame::Save(Bonus_S);
}

void ABonus::FindReferences(const USaveGame*& SaveGameObject, const TMap<FString, AActor*>& ExistActors)
{
	ISaveAndLoadGame::FindReferences(SaveGameObject, ExistActors);
}

void ABonus::Load(const USaveGame*& SaveGameObject)
{
	ISaveAndLoadGame::Load(SaveGameObject);
	auto Bonus_S = Cast<UBonus_S>(SaveGameObject);
	SetActorScale3D(Bonus_S->Scale);
}
