#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SaveGame.h"
#include "Paddle_S.generated.h"

UCLASS()
class ARKANOID_API UPaddle_S : public USaveGame
{
	GENERATED_BODY()

public:
	UPROPERTY()	int32 Lives = 0;
	UPROPERTY()	FString CurrentBallName = " ";
};
