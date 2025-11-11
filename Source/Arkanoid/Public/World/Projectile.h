#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Projectile.generated.h"

UCLASS()
class ARKANOID_API AProjectile : public AActor
{
	GENERATED_BODY()

public:
	AProjectile();
	
protected:
	virtual void BeginPlay() override;
	virtual void NotifyHit(class UPrimitiveComponent* MyComp, AActor* Other, class UPrimitiveComponent* OtherComp,
	                       bool bSelfMoved, FVector HitLocation, FVector HitNormal, FVector NormalImpulse,
	                       const FHitResult& Hit) override;

private:
	void Move();
	
	FTimerHandle Timer;
	
	UPROPERTY(EditDefaultsOnly)	UStaticMeshComponent* ProjectileMesh;
	UPROPERTY(EditDefaultsOnly)	float Speed = 3000.f;
	UPROPERTY(EditDefaultsOnly)	int32 Power = 8;
};
