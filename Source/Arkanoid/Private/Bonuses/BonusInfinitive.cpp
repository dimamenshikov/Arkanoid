#include "Bonuses/BonusInfinitive.h"
#include "Bonuses/SaveClasses/BonusInfinitive_S.h"
#include "Framework/Paddle.h"
#include "Kismet/GameplayStatics.h"

void ABonusInfinitive::Update()
{
	Activate();
}

void ABonusInfinitive::BonusTake()
{
	if (!IgnoreOtherBonus)
	{
		for (auto& Bonus : Paddle->Bonuses)
		{
			if (Bonus->GetClass() == GetClass())
			{
				if (ReplaceOldBonus)
				{
					Bonus->DeleteBonus();
					break;
				}
				else
				{
					Bonus->Update();
					Destroy();
					return;
				}
			}
		}
	}
	Paddle->Bonuses.Add(this);
	Paddle->OnBallDead.AddDynamic(this, &ABonusInfinitive::DeleteBonus);

	CheckPairedBonuses();

	Super::BonusTake();
}

void ABonusInfinitive::DeleteBonus()
{
	Paddle->Bonuses.Remove(this);
	Destroy();
}

void ABonusInfinitive::CheckPairedBonuses()
{
	for (int32 Index = 0; Index < Paddle->Bonuses.Num(); ++Index)
	{
		if (int32 i; PairedBonuses.Find(Paddle->Bonuses[Index]->GetClass(), i))
		{
			Paddle->Bonuses[Index]->Destroy();
			Paddle->Bonuses.RemoveAt(Index);
			--Index;
		}
	}
}

USaveGame* ABonusInfinitive::Save(USaveGame* BaseSaveObject)
{
	INIT_SAVE_OBJECT(UBonusInfinitive_S, BonusInfinitive_S);
	if (Paddle) BonusInfinitive_S->OwnerPaddle = Paddle->GetName();
	SET_VAL_1(BonusInfinitive_S, Value, SAVE);
	return Super::Save(BonusInfinitive_S);
}

void ABonusInfinitive::FindReferences(const USaveGame*& SaveGameObject, const TMap<FString, AActor*>& ExistActors)
{
	Super::FindReferences(SaveGameObject, ExistActors);
	auto BonusInfinitive_S = Cast<UBonusInfinitive_S>(SaveGameObject);
	Paddle = Cast<APaddle>(ExistActors.FindRef(BonusInfinitive_S->OwnerPaddle));
}

void ABonusInfinitive::Load(const USaveGame*& SaveGameObject)
{
	Super::Load(SaveGameObject);
	auto BonusInfinitive_S = Cast<UBonusInfinitive_S>(SaveGameObject);
	SET_VAL_1(BonusInfinitive_S, Value, LOAD);
	if (Paddle && AutoActivateForLoad)
	{
		BonusTake();
	}
}
