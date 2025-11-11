#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SaveGame.h"
#include "MainSave.generated.h"

UCLASS()
class ARKANOID_API UMainSave : public USaveGame
{
	GENERATED_BODY()

public:
	UPROPERTY()	TArray<FString> Slots;
	UPROPERTY()	int32 Record = 0;
};
