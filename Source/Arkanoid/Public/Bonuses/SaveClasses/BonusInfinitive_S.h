#pragma once

#include "CoreMinimal.h"
#include "Bonus_S.h"
#include "BonusInfinitive_S.generated.h"

UCLASS()
class ARKANOID_API UBonusInfinitive_S : public UBonus_S
{
	GENERATED_BODY()

public:
	UPROPERTY()	FString OwnerPaddle = " ";
	UPROPERTY()	float Value = 0.0;
};
