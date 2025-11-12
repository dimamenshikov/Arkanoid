#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Interface/SaveAndLoadGame.h"
#include "Interface/StartEvents.h"
#include "Bonus.generated.h"

class APaddle;

UCLASS(Abstract)
class ARKANOID_API ABonus : public AActor, public IStartEvents, public ISaveAndLoadGame
{
	GENERATED_BODY()

public:
	ABonus();

	virtual void Activate()	{};
	void ActiveMove(bool Move);
	
	UPROPERTY(EditAnywhere)	UStaticMeshComponent* BonusMesh = nullptr;
	UPROPERTY()	APaddle* Paddle = nullptr;
	UPROPERTY(EditAnywhere)	float Value = 1.0f;
	
protected:
	virtual void BeginPlay() override;

	virtual void StartGame() override;

	virtual void NotifyActorBeginOverlap(AActor* OtherActor) override;

	virtual void BonusTake();
	
	virtual USaveGame* Save(USaveGame* BaseSaveObject = nullptr) override;
	virtual void FindReferences(const USaveGame*& SaveGameObject, const TMap<FString, AActor*>& ExistActors) override;
	virtual void Load(const USaveGame*& SaveGameObject) override;

	FTimerHandle Timer;
	
private:
	UPROPERTY(EditDefaultsOnly)	USoundWave* SoundActivation = nullptr;
	UPROPERTY(EditAnywhere)	float BonusSpeed = 1000.0f;
	
	FVector VectorMove = FVector(-1.f, 0.f, 0.f);
};
