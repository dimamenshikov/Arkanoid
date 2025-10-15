#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Interface/Interaction.h"
#include "Block.generated.h"

class ABonus;
class ULifeBlock;

UCLASS()
class ARKANOID_API ABlock : public AActor, public IInteraction
{
	GENERATED_BODY()

protected:
	UPROPERTY(EditDefaultsOnly)
	UStaticMeshComponent* StaticMesh = nullptr;

	virtual void BeginPlay() override;
	virtual void Interaction(class ABall* Ball, const FHitResult& HitResult) override;

public:
	ABlock();

	UMaterialInstanceDynamic* Material = nullptr;
	TSubclassOf<ABonus> BonusClass = nullptr;
	
	UPROPERTY(EditDefaultsOnly)
	ULifeBlock* LifeComponent = nullptr;
	UPROPERTY(EditDefaultsOnly)
	int32 Score = 0;
	UPROPERTY(EditDefaultsOnly)
	USoundWave* SoundDestroy = nullptr;
	UPROPERTY(EditDefaultsOnly)
	UParticleSystem* EffectDestroy = nullptr;
	
	void Exterminate();
};
