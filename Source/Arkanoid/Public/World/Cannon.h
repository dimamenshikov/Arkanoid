#pragma once

#include "CoreMinimal.h"
#include "Framework/ArkanoidGameplayClasses.h"
#include "GameFramework/Actor.h"
#include "Cannon.generated.h"

class ABonusCannon;
class AProjectile;

UCLASS()
class ARKANOID_API ACannon : public AActor
{
	GENERATED_BODY()

public:
	ACannon();
	
	void Shoot();
	
	UPROPERTY(EditDefaultsOnly)	UStaticMeshComponent* CannonMesh = nullptr;

private:
	UPROPERTY(EditDefaultsOnly)	UArkanoidGameplayClasses* GameplayClasses = nullptr;
	
	UPROPERTY(EditDefaultsOnly)	TSubclassOf<AProjectile> ProjectileClass;
	UPROPERTY(EditDefaultsOnly)	USceneComponent* ShootPoint = nullptr;
};
