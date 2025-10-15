#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SaveGame.h"
#include "SaveSlot.generated.h"

UCLASS()
class ARKANOID_API USaveSlot : public USaveGame
{
	GENERATED_BODY()

public:
	UPROPERTY()
	int32 PlayerScore = 0;
};
