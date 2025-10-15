#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "ArkanoidGM_MainMenu.generated.h"

class UMainMenuWidget;

UCLASS(Abstract)
class ARKANOID_API AArkanoidGM_MainMenu : public AGameModeBase
{
	GENERATED_BODY()

protected:
	virtual void BeginPlay() override;
	UMainMenuWidget* MainMenu = nullptr;
	UPROPERTY(EditDefaultsOnly)
	USoundWave* LevelMusic = nullptr;

public:
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UUserWidget> MainMenuWidgetClass;
};
