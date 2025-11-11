#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Interface/SaveAndLoadGame.h"
#include "Interface/StartEvents.h"
#include "Ball.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnBallHit, const FHitResult&, Hit);

class APaddle;

UCLASS()
class ARKANOID_API ABall : public AActor, public IStartEvents, public ISaveAndLoadGame
{
	GENERATED_BODY()

public:
	ABall();

	void ActiveMove(const bool Active);
	void Init(APaddle* OwnerPaddle);
	
	UPROPERTY(EditDefaultsOnly)	UStaticMeshComponent* StaticMesh = nullptr;
	
	FOnBallHit OnBallHit;
	FVector NextDirection, CurrentDirection, PreviousLocation, NextLocation;
	int32 Power = 0;
	float Speed = 0.0f;
	bool bMovement = false;
	
protected:
	virtual void StartGame() override;
	
	virtual void NotifyHit(UPrimitiveComponent* MyComp, AActor* Other, UPrimitiveComponent* OtherComp, bool bSelfMoved,
	                       FVector HitLocation, FVector HitNormal, FVector NormalImpulse,
	                       const FHitResult& Hit) override;
	
	virtual USaveGame* Save(USaveGame* BaseSaveObject = nullptr) override;
	virtual void FindReferences(const USaveGame*& SaveGameObject, const TMap<FString, AActor*>& ExistActors) override;
	virtual void Load(const USaveGame*& SaveGameObject) override;

private:
	UFUNCTION()	void Move();
	
	UPROPERTY(EditDefaultsOnly)	USoundWave* SoundHit = nullptr;

	FTimerHandle Timer;
	bool CanSoundHit = true;
};
