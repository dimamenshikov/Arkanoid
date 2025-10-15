#include "Arkanoid/Public/Widgets/PauseWidget.h"
#include "Arkanoid/Public/Framework/ArkanoidGameplayClasses.h"
#include "Arkanoid/Public/Framework/ArkanoidGI.h"
#include "Arkanoid/Public/Framework/ArkanoidGM.h"
#include "Arkanoid/Public/Framework/ArkanoidHUD.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"
#include "Kismet/GameplayStatics.h"

void UPauseWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	Continue_B->OnReleased.AddDynamic(this, &UPauseWidget::Continue);
	Quit_B->OnReleased.AddDynamic(this, &UPauseWidget::Quit);
	InMainMenu_B->OnReleased.AddDynamic(this, &UPauseWidget::InMainMenu);
}

void UPauseWidget::NativeConstruct()
{
	Super::NativeConstruct();

	const FString ScoreString = FString::Printf(TEXT("Рекорд: %03d"), GameplayClasses->ArkanoidGI->Record);
	Record_T->SetText(FText::FromString(ScoreString));
}

void UPauseWidget::Continue()
{
	if (GameplayClasses->ArkanoidHUD->bPause)
	{
		GameplayClasses->ArkanoidGM->SetGamePause();
	}
	else
	{
		UGameplayStatics::OpenLevel(this, FName("Arkanoid"));
	}
}

void UPauseWidget::InMainMenu()
{
	UGameplayStatics::OpenLevel(this, "MainMenu");
}

void UPauseWidget::Quit()
{
	UKismetSystemLibrary::QuitGame(this, UGameplayStatics::GetPlayerController(this, 0),
	                               EQuitPreference::Quit, true);
}
