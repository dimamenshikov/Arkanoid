#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "ArkanoidGI.generated.h"

class UMainSave;
class UArkanoidGameplayClasses;
class USlotSave;

UCLASS(Abstract)
class ARKANOID_API UArkanoidGI : public UGameInstance
{
	GENERATED_BODY()

public:
	void AddLives(const int32 AddLives);
	void SaveGame();
	void LoadGame(const FString& SlotName);
	void ClearRecord();
	void DeleteSlot(const FString& SlotName);
	void Pause(bool Pause);

	UPROPERTY()
	UMainSave* MainSave = nullptr;
	UPROPERTY(EditDefaultsOnly)
	TArray<FString> Levels;

	int32 Record = 0;
	int32 Score = 0;
	int32 Lives = 3;
	bool LevelLoad = false;
	bool StartGame = false;
	bool CanSaveGame = true;
	bool CanSaveTime = true;

	bool FirstLaunch = true;

protected:
	virtual void Init() override;
	virtual void LoadComplete(const float LoadTime, const FString& MapName) override;

private:
	void LoadLevel();

	UPROPERTY(EditDefaultsOnly)
	UArkanoidGameplayClasses* GameplayClasses = nullptr;

	UPROPERTY()
	USlotSave* SlotSave = nullptr;

	FTimerHandle Timer;
	FString LoadingSlot = " ";
	bool TimerCanSaveActive = false;
};
