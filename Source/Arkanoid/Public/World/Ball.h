#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Ball.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnBallHit, const FHitResult&, Hit);

class APaddle;

UCLASS()
class ARKANOID_API ABall : public AActor
{
	GENERATED_BODY()

public:
	ABall();
	
	UPROPERTY(EditDefaultsOnly)
	USoundWave* SoundHit = nullptr;
	UPROPERTY(EditDefaultsOnly)
	UStaticMeshComponent* StaticMesh = nullptr;

	int32 Power = 0;
	float Speed = 0.0f;
	APaddle* Paddle = nullptr;
	FOnBallHit OnBallHit;
	bool bMovement = false;
	FVector NextDirection, CurrentDirection, PreviousLocation, NextLocation;

	void Init(APaddle* OwnerPaddle);
	void Move(float DeltaSeconds);
	virtual void Tick(float DeltaSeconds) override;
	virtual void NotifyHit(UPrimitiveComponent* MyComp, AActor* Other, UPrimitiveComponent* OtherComp, bool bSelfMoved,
	                       FVector HitLocation, FVector HitNormal, FVector NormalImpulse,
	                       const FHitResult& Hit) override;
};
