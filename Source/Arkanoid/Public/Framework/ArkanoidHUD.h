#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "ArkanoidHUD.generated.h"

class UPauseWidget;
class UInterfaceWidget;
class UArkanoidGameplayClasses;

UCLASS()
class ARKANOID_API AArkanoidHUD : public AHUD
{
	GENERATED_BODY()

private:
	FTimerHandle Timer;
	void LevelLoad();
	UPauseWidget* Pause = nullptr;
	float Time = 0.0f;

	UFUNCTION()
	void UpdateScore(const int32 NewScore);
	void UpdateTime();

protected:
	UPROPERTY(EditDefaultsOnly)
	UArkanoidGameplayClasses* GameplayClasses = nullptr;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UUserWidget> InterfaceClass;
	UInterfaceWidget* Interface = nullptr;
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UUserWidget> PauseClass;

	virtual void Tick(float DeltaSeconds) override;
	virtual void BeginPlay() override;

public:
	bool bPause = true;

	void EndGame(bool bWin);
	void SetPause(const bool bPause);
};
