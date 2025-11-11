#include "Arkanoid/Public/Framework/ArkanoidHUD_MainMenu.h"
#include "Blueprint/UserWidget.h"
#include "Kismet/GameplayStatics.h"

void AArkanoidHUD_MainMenu::LevelLoad()
{
	UGameplayStatics::GetPlayerController(this, 0)->SetShowMouseCursor(true);
	UGameplayStatics::GetPlayerController(this, 0)->SetInputMode(FInputModeUIOnly());

	CreateWidget(PlayerOwner, MainMenuWidgetClass)->AddToViewport();
}
