#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "ArkanoidHUD_MainMenu.generated.h"

class UMainMenuWidget;

UCLASS()
class ARKANOID_API AArkanoidHUD_MainMenu : public AHUD
{
	GENERATED_BODY()

private:
	FTimerHandle Timer;
	
protected:
	void LevelLoad();
	virtual void BeginPlay() override;
};
