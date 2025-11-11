#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Interface/Interaction.h"
#include "Interface/SaveAndLoadGame.h"
#include "Block.generated.h"

class ABonus;
class ULifeBlock;

UCLASS()
class ARKANOID_API ABlock : public AActor, public IInteraction, public ISaveAndLoadGame
{
	GENERATED_BODY()

public:
	ABlock();
	
	void Exterminate();
	
	UPROPERTY(EditDefaultsOnly)	ULifeBlock* LifeComponent = nullptr;
	UPROPERTY(EditDefaultsOnly)	int32 Score = 0;
	
	UMaterialInstanceDynamic* Material = nullptr;
	TSubclassOf<ABonus> BonusClass = nullptr;
	
protected:
	virtual void BeginPlay() override;
	virtual void Interaction(class ABall* Ball, const FHitResult& HitResult) override;

	virtual USaveGame* Save(USaveGame* BaseSaveObject = nullptr) override;
	virtual void Load(const USaveGame*& SaveGameObject) override;
	
	UPROPERTY(EditDefaultsOnly)	UStaticMeshComponent* StaticMesh = nullptr;

private:
	UPROPERTY(EditDefaultsOnly)	USoundWave* SoundDestroy = nullptr;
	UPROPERTY(EditDefaultsOnly)	UParticleSystem* EffectDestroy = nullptr;
};
