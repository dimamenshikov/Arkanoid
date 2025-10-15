#include "Arkanoid/Public/Framework/ArkanoidHUD_MainMenu.h"
#include "Arkanoid/Public/Framework/ArkanoidGM_MainMenu.h"
#include "Blueprint/UserWidget.h"
#include "Kismet/GameplayStatics.h"

void AArkanoidHUD_MainMenu::LevelLoad()
{
	UGameplayStatics::GetPlayerController(this, 0)->SetShowMouseCursor(true);
	UGameplayStatics::GetPlayerController(this, 0)->SetInputMode(FInputModeUIOnly());

	CreateWidget(PlayerOwner, Cast<AArkanoidGM_MainMenu>(GetWorld()->GetAuthGameMode())->MainMenuWidgetClass)->
		AddToViewport();
}

void AArkanoidHUD_MainMenu::BeginPlay()
{
	Super::BeginPlay();

	GetWorldTimerManager().SetTimer(Timer, this, &AArkanoidHUD_MainMenu::LevelLoad, 0.1f, false);
}
