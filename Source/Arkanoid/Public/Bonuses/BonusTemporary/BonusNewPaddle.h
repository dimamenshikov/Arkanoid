#pragma once

#include "CoreMinimal.h"
#include "Bonuses/BonusTemporary.h"
#include "BonusNewPaddle.generated.h"

UCLASS(Abstract)
class ARKANOID_API ABonusNewPaddle : public ABonusTemporary
{
	GENERATED_BODY()

protected:
	virtual void Activate() override;
	virtual void Update() override;
	
	virtual void NotifyHit(class UPrimitiveComponent* MyComp, AActor* Other, class UPrimitiveComponent* OtherComp,
	                       bool bSelfMoved, FVector HitLocation, FVector HitNormal, FVector NormalImpulse,
	                       const FHitResult& Hit) override;

	virtual void Load(const USaveGame*& SaveGameObject) override;
	
private:
	void MovePaddle();
	
	float Speed = 500.0f;
	bool Loading = false;
};
