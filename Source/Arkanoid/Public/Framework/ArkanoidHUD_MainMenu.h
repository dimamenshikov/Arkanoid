#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "Interface/StartEvents.h"
#include "ArkanoidHUD_MainMenu.generated.h"

class UMainMenuWidget;

UCLASS()
class ARKANOID_API AArkanoidHUD_MainMenu : public AHUD, public IStartEvents
{
	GENERATED_BODY()

protected:
	virtual void LevelLoad() override;

private:
	UPROPERTY(EditDefaultsOnly)	TSubclassOf<UUserWidget> MainMenuWidgetClass;
};
