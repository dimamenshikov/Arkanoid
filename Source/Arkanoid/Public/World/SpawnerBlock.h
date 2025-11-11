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
class ARKANOID_API ASpawnerBlock : public AActor, public ISaveAndLoadGame, public IStartEvents
{
	GENERATED_BODY()

public:
	ASpawnerBlock();

protected:
	virtual void OnConstruction(const FTransform& Transform) override;
	virtual void LevelLoad() override;
	
	virtual USaveGame* Save(USaveGame* BaseSaveObject = nullptr) override;
	virtual void FindReferences(const USaveGame*& SaveGameObject, const TMap<FString, AActor*>& ExistActors) override;

private:
	UFUNCTION()	void OnBlockDestroyed(AActor* DestroyedBlock);
	void CreateComponent();
	void ClearComponents();
	void SpawnBlock();
	TSubclassOf<ABonus> GetBonusClass() const;

	USceneComponent* Scene = nullptr;
	UPROPERTY()	TArray<ABlock*> BlockActors;
	UPROPERTY()	TArray<UStaticMeshComponent*> Components;

	UPROPERTY(EditAnywhere)	TArray<FBonusTypeChance> BonusTypeChance;
	UPROPERTY(EditAnywhere)	float BonusChance = 0.0f;
	UPROPERTY(EditAnywhere)	TSubclassOf<ABlock> BlockClass;
	UPROPERTY(EditAnywhere)	float GridSizeX = 1.0f;
	UPROPERTY(EditAnywhere)	float GridSizeY = 1.0f;
	UPROPERTY(EditAnywhere)	float SpacerX = 1.0f;
	UPROPERTY(EditAnywhere)	float SpacerY = 1.0f;
	UPROPERTY(EditAnywhere)	FVector Scale;
	UPROPERTY(EditAnywhere)	UStaticMesh* Mesh = nullptr;
};
