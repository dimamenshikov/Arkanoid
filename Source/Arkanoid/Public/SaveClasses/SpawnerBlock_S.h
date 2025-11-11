#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SaveGame.h"
#include "SpawnerBlock_S.generated.h"

UCLASS()
class ARKANOID_API USpawnerBlock_S : public USaveGame
{
	GENERATED_BODY()

public:
	UPROPERTY()
	TArray<FString> Blocks;
};
