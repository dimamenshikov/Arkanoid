#pragma once

#include "CoreMinimal.h"
#include "BonusTemporary_S.h"
#include "BonusShuriken_S.generated.h"

UCLASS()
class ARKANOID_API UBonusShuriken_S : public UBonusTemporary_S
{
	GENERATED_BODY()

public:
	UPROPERTY()	UStaticMesh* OldStaticMesh = nullptr;
	UPROPERTY()	UMaterialInterface* OldMaterial = nullptr;
	UPROPERTY()	FVector OldScale;
};
