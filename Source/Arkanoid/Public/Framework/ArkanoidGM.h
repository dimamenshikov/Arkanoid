#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "ArkanoidGM.generated.h"

class UArkanoidGameplayClasses;

UCLASS(Abstract)
class ARKANOID_API AArkanoidGM : public AGameModeBase
{
	GENERATED_BODY()

private:
	bool bWin = false;
	FTimerHandle Timer;

	void EndGame();

protected:
	UAudioComponent* LevelMusic = nullptr;
	UPROPERTY(EditDefaultsOnly)
	USoundWave* LevelMusicClass = nullptr;
	UPROPERTY(EditDefaultsOnly)
	UArkanoidGameplayClasses* GameplayClasses = nullptr;

	UPROPERTY(EditDefaultsOnly)
	USoundWave* SoundWin = nullptr;
	UPROPERTY(EditDefaultsOnly)
	USoundWave* SoundDefeat = nullptr;

	virtual void BeginPlay() override;

public:
	void SetGamePause();
	void GameEnd(bool Win);
};
