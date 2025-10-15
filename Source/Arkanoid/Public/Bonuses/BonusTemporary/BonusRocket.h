#pragma once

#include "CoreMinimal.h"
#include "Arkanoid/Public/Bonuses/Bonus.h"
#include "BonusRocket.generated.h"

UCLASS(Abstract)
class ARKANOID_API ABonusRocket : public ABonus
{
	GENERATED_BODY()

	//					Parent:

	// Variable

	// Function
public:
	ABonusRocket();

protected:
	virtual void NotifyActorBeginOverlap(AActor* OtherActor) override;
	virtual void NotifyHit(class UPrimitiveComponent* MyComp, AActor* Other, class UPrimitiveComponent* OtherComp,
	                       bool bSelfMoved, FVector HitLocation, FVector HitNormal, FVector NormalImpulse,
	                       const FHitResult& Hit) override;


	//					Gameplay:

	// Variable
private:
	UPROPERTY(EditDefaultsOnly, meta = (AllowPrivateAccess = true))
	UParticleSystem* EffectDestroy = nullptr;
	UPROPERTY(EditDefaultsOnly, meta = (AllowPrivateAccess = true))
	UStaticMesh* RocketMesh = nullptr;
	UPROPERTY(EditDefaultsOnly, meta = (AllowPrivateAccess = true))
	UMaterialInterface* RocketMaterial = nullptr;

	float SpeedShuriken = 500.0f;

	// Function
protected:
	virtual void BonusAction(ABonus* OldBonus) override;

private:
	void MoveRocket(); // Двжиение ракеты
};
