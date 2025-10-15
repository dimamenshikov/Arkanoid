#pragma once

#include "CoreMinimal.h"
#include "Arkanoid/Public/Bonuses/Bonus.h"
#include "BonusShield.generated.h"

UCLASS(Abstract)
class ARKANOID_API ABonusShield : public ABonus
{
	GENERATED_BODY()

	//					Parent:

	// Variable

	// Function
public:
	ABonusShield();

	//					Gameplay:

	// Variable
private:
	UPROPERTY(EditAnywhere, meta = (AllowPrivateAccess = true))
	UStaticMesh* ShieldMesh = nullptr;
	UPROPERTY(EditAnywhere, meta = (AllowPrivateAccess = true))
	UMaterialInterface* ShieldMaterial = nullptr;

	// Function
protected:
	virtual void BonusAction(ABonus* OldBonus) override;
};
