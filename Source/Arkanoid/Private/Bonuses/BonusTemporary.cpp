#include "Bonuses/BonusTemporary.h"
#include "Bonuses/SaveClasses/BonusTemporary_S.h"
#include "Kismet/GameplayStatics.h"

void ABonusTemporary::BeginPlay()
{
	Super::BeginPlay();

	BonusDuration = BonusLife;
}

void ABonusTemporary::BonusTake()
{
	Super::BonusTake();

	if (!LoadingComplete)
	{
		GetWorldTimerManager().SetTimer(TimerBonusLife, this, &ABonusTemporary::DeleteBonus, BonusDuration, false);
	}
}

void ABonusTemporary::Update()
{
	if (UpdateTime)
	{
		GetWorldTimerManager().SetTimer(TimerBonusLife, this, &ABonusTemporary::DeleteBonus, BonusDuration, false);
		return;
	}
	Activate();
}

void ABonusTemporary::StartGame()
{
	ABonus::StartGame();

	if (LoadingComplete && Paddle)
	{
		Update();
		BonusDuration = BonusLife;
	}
}

USaveGame* ABonusTemporary::Save(USaveGame* BaseSaveObject)
{
	INIT_SAVE_OBJECT(UBonusTemporary_S, BonusTemporary_S);
	BonusDuration = GetWorldTimerManager().GetTimerRemaining(TimerBonusLife);
	if (Paddle && BonusDuration != -1.f)
	{
		SET_VAL_1(BonusTemporary_S, BonusDuration, SAVE);
	}
	return Super::Save(BonusTemporary_S);
}

void ABonusTemporary::FindReferences(const USaveGame*& SaveGameObject, const TMap<FString, AActor*>& ExistActors)
{
	Super::FindReferences(SaveGameObject, ExistActors);
}

void ABonusTemporary::Load(const USaveGame*& SaveGameObject)
{
	Super::Load(SaveGameObject);
	auto BonusTemporary_S = Cast<UBonusTemporary_S>(SaveGameObject);
	if (BonusTemporary_S->BonusDuration != -1.f)
	{
		SET_VAL_1(BonusTemporary_S, BonusDuration, LOAD);
	}
}
