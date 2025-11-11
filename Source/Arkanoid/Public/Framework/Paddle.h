#pragma once

#include "Arkanoid/Public/Interface/Interaction.h"
#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Interface/SaveAndLoadGame.h"
#include "Interface/StartEvents.h"
#include "Paddle.generated.h"

class ABonusInfinitive;
class UArkanoidGameplayClasses;
class UCameraComponent;
class UInputMappingContext;
class UArrowComponent;
class UBoxComponent;
class UInputAction;
struct FInputActionValue;

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnBallDead);

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnLifeChange, const int32, NewLives);

USTRUCT(BlueprintType)
struct FDataSetting
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere)	float DefaultBallSpeed = 2000.0f;
	UPROPERTY(EditAnywhere)	float MinBallSpeed = 500.0f;
	UPROPERTY(EditAnywhere)	float MaxBallSpeed = 2500.0f;

	UPROPERTY(EditAnywhere)	float DefaultSizePaddle = 100.0f;
	UPROPERTY(EditAnywhere)	float MinSizePaddle = 50.0f;
	UPROPERTY(EditAnywhere)	float MaxSizePaddle = 300.0f;

	UPROPERTY(EditAnywhere)	int32 DefaultPower = 10;
	UPROPERTY(EditAnywhere)	int32 MinPower = 5;
	UPROPERTY(EditAnywhere)	int32 MaxPower = 20;
};

UCLASS(Abstract)
class ARKANOID_API APaddle : public APawn, public IInteraction, public ISaveAndLoadGame, public IStartEvents
{
	GENERATED_BODY()

public:
	APaddle();
	
	UFUNCTION()	void BallDead(AActor* Destroyed);
	
	void SpawnBall();

	UPROPERTY(EditDefaultsOnly)	UArkanoidGameplayClasses* GameplayClasses = nullptr;
	
	UPROPERTY(EditAnywhere)	UCameraComponent* Camera = nullptr;
	UPROPERTY(VisibleAnywhere)	UStaticMeshComponent* StaticMesh = nullptr;
	UPROPERTY(EditAnywhere)	UBoxComponent* BoxCollisionRoot = nullptr;
	UPROPERTY(VisibleAnywhere)	UArrowComponent* Arrow = nullptr;
	
	UPROPERTY(EditAnywhere)	FDataSetting GameplaySetting;
	UPROPERTY()	TArray<ABonusInfinitive*> Bonuses;
	UPROPERTY()	ABall* CurrentBall = nullptr;
	UPROPERTY(EditDefaultsOnly)	float PaddleSpeed = 100.0f;
	
	FOnLifeChange OnLifeChange;
	FOnBallDead OnBallDead;
	float CameraRotationYaw = 0.0f;
	
protected:
	virtual void OnConstruction(const FTransform& Transform) override;
	virtual void BeginPlay() override;
	
	virtual void LevelLoad() override;

	virtual void Interaction(ABall* Ball, const FHitResult& HitResult) override;

	virtual USaveGame* Save(USaveGame* BaseSaveObject = nullptr) override;
	virtual void FindReferences(const USaveGame*& SaveGameObject, const TMap<FString, AActor*>& ExistActors) override;

private:
	UPROPERTY(VisibleAnywhere)	UStaticMeshComponent* LeftStaticMesh = nullptr;
	UPROPERTY(VisibleAnywhere)	UStaticMeshComponent* RightStaticMesh = nullptr;
	UPROPERTY(EditAnywhere)	UStaticMesh* Meshes = nullptr;
	UPROPERTY(EditDefaultsOnly)	TSubclassOf<AActor> ClassBall = nullptr;
	UPROPERTY(EditDefaultsOnly)	USoundWave* SoundBallDeath = nullptr;
};
