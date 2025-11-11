#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SaveGame.h"
#include "LifeBlock_S.generated.h"

class ABonus;

UCLASS()
class ARKANOID_API ULifeBlock_S : public USaveGame
{
	GENERATED_BODY()

public:
	UPROPERTY()	int32 Score = 0;
	UPROPERTY()	int32 MaxLife = 0;
	UPROPERTY()	int32 Life = 0;
	UPROPERTY()	TSubclassOf<ABonus> BonusClass;
};
