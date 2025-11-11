#pragma once

#include "CoreMinimal.h"
#include "BonusInfinitive_S.h"
#include "BonusNewBall_S.generated.h"

UCLASS()
class ARKANOID_API UBonusNewBall_S : public UBonusInfinitive_S
{
	GENERATED_BODY()

public:
	UPROPERTY()	TArray<FString> Balls;
};
