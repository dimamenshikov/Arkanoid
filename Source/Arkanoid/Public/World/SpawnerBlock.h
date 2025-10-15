#pragma once

#include "CoreMinimal.h"
#include "Bonuses/Bonus.h"
#include "GameFramework/Actor.h"
#include "SpawnerBlock.generated.h"

class ABlock;

USTRUCT()
struct FBonusTypeChance
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere)
	float DropChance = 1.0f;
	UPROPERTY(EditAnywhere)
	TSubclassOf<ABonus> BonusClass;
};

UCLASS()
class ARKANOID_API ASpawnerBlock : public AActor
{
	GENERATED_BODY()

public:
	ASpawnerBlock();

protected:
	USceneComponent* Scene = nullptr;
	
	virtual void OnConstruction(const FTransform& Transform) override;
	virtual void BeginPlay() override;
	
	void CreateComponent();
	void ClearComponents();
	void SpawnBlock();
	UFUNCTION()	void OnBlockDestroyed(AActor* DestroyedBlock);

	TSubclassOf<ABonus> GetBonusClass() const;

	UPROPERTY(EditAnywhere)
	TArray<FBonusTypeChance> BonusTypeChance;
	UPROPERTY(EditAnywhere)
	float BonusChance = 0.0f;
	UPROPERTY(EditAnywhere)
	TSubclassOf<ABlock> BlockClass;
	UPROPERTY(EditAnywhere)
	float GridSizeX = 1.0f;
	UPROPERTY(EditAnywhere)
	float GridSizeY = 1.0f;
	UPROPERTY(EditAnywhere)
	float SpacerX = 1.0f;
	UPROPERTY(EditAnywhere)
	float SpacerY = 1.0f;
	UPROPERTY(EditAnywhere)
	FVector Scale;
	UPROPERTY(EditAnywhere)
	UStaticMesh* Mesh = nullptr;

	UPROPERTY()
	TArray<UStaticMeshComponent*> Components;
	TArray<ABlock*> BlockActors;
};
