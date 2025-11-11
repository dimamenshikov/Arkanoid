#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SaveGame.h"
#include "Bonus_S.generated.h"

UCLASS()
class ARKANOID_API UBonus_S : public USaveGame
{
	GENERATED_BODY()

public:
	UPROPERTY()	FVector Scale = FVector::ZeroVector;
};
