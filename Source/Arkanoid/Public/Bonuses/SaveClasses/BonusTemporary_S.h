#pragma once

#include "CoreMinimal.h"
#include "BonusInfinitive_S.h"
#include "BonusTemporary_S.generated.h"

UCLASS()
class ARKANOID_API UBonusTemporary_S : public UBonusInfinitive_S
{
	GENERATED_BODY()

public:
	UPROPERTY()	float BonusDuration = -1.f;
};
