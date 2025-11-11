#pragma once

#include "CoreMinimal.h"
#include "Bonuses/BonusTemporary.h"
#include "BonusShield.generated.h"

UCLASS(Abstract)
class ARKANOID_API ABonusShield : public ABonusTemporary
{
	GENERATED_BODY()

protected:
	virtual void Activate() override;
	
private:
	UPROPERTY(EditAnywhere)	UStaticMesh* ShieldMesh = nullptr;
	UPROPERTY(EditAnywhere)	UMaterialInterface* ShieldMaterial = nullptr;
};
