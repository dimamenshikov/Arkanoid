#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "Interface/SaveAndLoadGame.h"
#include "Interface/StartEvents.h"
#include "ArkanoidHUD.generated.h"

class UPauseWidget;
class UInterfaceWidget;
class UArkanoidGameplayClasses;

UCLASS()
class ARKANOID_API AArkanoidHUD : public AHUD, public IStartEvents, public ISaveAndLoadGame
{
	GENERATED_BODY()

public:
	void EndGame(bool bWin);
	void SetPause(const bool bPause);

	UPROPERTY(EditDefaultsOnly)	UArkanoidGameplayClasses* GameplayClasses = nullptr;

	bool bPause = true;
	
protected:
	virtual void BeginPlay() override;
	
	virtual void LevelLoad() override;
	virtual void StartGame() override;
	
	virtual USaveGame* Save(USaveGame* BaseSaveObject = nullptr) override;
	virtual void Load(const USaveGame*& SaveGameObject) override;

private:
	UFUNCTION()	void UpdateScore(const int32 NewScore);
	UFUNCTION()	void UpdateLives(const int32 NewLives);
	
	void UpdateTime();
	void ShowTime();
		
	UPROPERTY(EditDefaultsOnly)	TSubclassOf<UUserWidget> InterfaceClass;
	UPROPERTY(EditDefaultsOnly)	TSubclassOf<UUserWidget> PauseClass;
	
	UPROPERTY()	UInterfaceWidget* Interface = nullptr;
	UPROPERTY()	UPauseWidget* Pause = nullptr;
	
	FTimerHandle Timer;
	float Time = 0.0f;
};
