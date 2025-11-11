#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "Interface/StartEvents.h"
#include "ArkanoidGM.generated.h"

class ABlock;
class UArkanoidGameplayClasses;

UCLASS(Abstract)
class ARKANOID_API AArkanoidGM : public AGameModeBase, public IStartEvents
{
	GENERATED_BODY()

public:
	AArkanoidGM();

	void SetGamePause();
	void GameEnd(const bool Win);
	
protected:
	virtual void BeginPlay() override;
	
	virtual void LevelLoad() override;
	virtual void StartGame() override;
	
private:
	UFUNCTION()	void DestroyBlock(AActor* Destroyed);
	
	UPROPERTY(EditDefaultsOnly)	UArkanoidGameplayClasses* GameplayClasses = nullptr;
	
	UPROPERTY(EditDefaultsOnly)	UAudioComponent* Music = nullptr;
	UPROPERTY(EditDefaultsOnly)	USoundWave* SoundWin = nullptr;
	UPROPERTY(EditDefaultsOnly)	USoundWave* SoundDefeat = nullptr;
	
	TArray<ABlock*> Blocks;
	bool bWin = false;
};
