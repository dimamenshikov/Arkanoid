#pragma once

#include "CoreMinimal.h"
#include "Bonuses/BonusInfinitive.h"
#include "BonusRocket.generated.h"

UCLASS(Abstract)
class ARKANOID_API ABonusRocket : public ABonusInfinitive
{
	GENERATED_BODY()

protected:
	virtual void StartGame() override;
	
	virtual void Activate() override;
	virtual void BonusTake() override;
	
	virtual void NotifyActorBeginOverlap(AActor* OtherActor) override;
	virtual void NotifyHit(class UPrimitiveComponent* MyComp, AActor* Other, class UPrimitiveComponent* OtherComp,
	                       bool bSelfMoved, FVector HitLocation, FVector HitNormal, FVector NormalImpulse,
	                       const FHitResult& Hit) override;

private:
	UPROPERTY(EditDefaultsOnly)	UParticleSystem* EffectDestroy = nullptr;

	float SpeedRocket = 1000.0f;
};
