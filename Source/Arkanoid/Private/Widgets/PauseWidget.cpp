#include "Arkanoid/Public/Widgets/PauseWidget.h"
#include "Arkanoid/Public/Framework/ArkanoidGameplayClasses.h"
#include "Arkanoid/Public/Framework/ArkanoidGI.h"
#include "Arkanoid/Public/Framework/ArkanoidGM.h"
#include "Arkanoid/Public/Framework/ArkanoidHUD.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"
#include "Components/WidgetSwitcher.h"
#include "Framework/ArkanoidPS.h"
#include "Kismet/GameplayStatics.h"
#include "Widgets/LoadMenuWidget.h"

void UPauseWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	Continue_B->OnReleased.AddDynamic(this, &UPauseWidget::Continue);
	Quit_B->OnReleased.AddDynamic(this, &UPauseWidget::Quit);
	InMainMenu_B->OnReleased.AddDynamic(this, &UPauseWidget::InMainMenu);
	Load_B->OnReleased.AddDynamic(this, &UPauseWidget::Load);
	Save_B->OnReleased.AddDynamic(this, &UPauseWidget::Save);
	Back_B->OnReleased.AddDynamic(this, &UPauseWidget::Back);
}

void UPauseWidget::NativeConstruct()
{
	Super::NativeConstruct();

	Score_T->SetText(
		FText::FromString(FString::Printf(TEXT("Счёт: %i"), Owner->GameplayClasses->ArkanoidPS->PlayerScore)));
	Record_T->SetText(
		FText::FromString(FString::Printf(TEXT("Рекорд: %i"), Owner->GameplayClasses->ArkanoidGI->Record)));
	Save_T->SetColorAndOpacity(
		Owner->GameplayClasses->ArkanoidGI->CanSaveGame && Owner->GameplayClasses->ArkanoidGI->CanSaveTime
			? FSlateColor(FLinearColor::White)
			: FSlateColor(FLinearColor(0.01f, 0.01f, 0.01f, 1.f)));
}

void UPauseWidget::Back()
{
	Switcher->SetActiveWidgetIndex(0);
}

void UPauseWidget::Continue()
{
	if (Owner->GameplayClasses->ArkanoidHUD->bPause)
	{
		Owner->GameplayClasses->ArkanoidGM->SetGamePause();
	}
	else
	{
		Owner->GameplayClasses->ArkanoidGI->Lives = 3;
		Owner->GameplayClasses->ArkanoidGI->Score = 0;
		UGameplayStatics::OpenLevel(this, "Arkanoid");
	}
}

void UPauseWidget::InMainMenu()
{
	UGameplayStatics::OpenLevel(this, "Menu");
}

void UPauseWidget::Quit()
{
	UKismetSystemLibrary::QuitGame(this, UGameplayStatics::GetPlayerController(this, 0),
	                               EQuitPreference::Quit, true);
}

void UPauseWidget::Load()
{
	LoadMenu->UpdateSaves();
	Switcher->SetActiveWidgetIndex(1);
}

void UPauseWidget::Save()
{
	Owner->GameplayClasses->ArkanoidGI->SaveGame();
	Save_T->SetColorAndOpacity(FSlateColor(FLinearColor(0.01f, 0.01f, 0.01f, 1.f)));
}
