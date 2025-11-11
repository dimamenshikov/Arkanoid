#include "Arkanoid/Public/Widgets/MainMenuWidget.h"
#include "Arkanoid/Public/Framework/ArkanoidGI.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"
#include "Components/WidgetSwitcher.h"
#include "Kismet/GameplayStatics.h"
#include "Widgets/LoadMenuWidget.h"

void UMainMenuWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	Start_B->OnReleased.AddDynamic(this, &UMainMenuWidget::StartGame);
	Quit_B->OnReleased.AddDynamic(this, &UMainMenuWidget::QuitGame);
	ZeroRecord_B->OnReleased.AddDynamic(this, &UMainMenuWidget::ClearRecord);
	Back_B->OnReleased.AddDynamic(this, &UMainMenuWidget::Back);
	Load_B->OnReleased.AddDynamic(this, &UMainMenuWidget::Load);
}

void UMainMenuWidget::NativeConstruct()
{
	Super::NativeConstruct();

	Record_T->SetText(
		FText::FromString(FString::Printf(TEXT("Рекорд: %03d"), Cast<UArkanoidGI>(GetGameInstance())->Record)));
}

void UMainMenuWidget::Load()
{
	LoadMenu->UpdateSaves();
	Switcher->SetActiveWidgetIndex(1);
}

void UMainMenuWidget::Back()
{
	Switcher->SetActiveWidgetIndex(0);
}

void UMainMenuWidget::StartGame()
{
	auto GI = Cast<UArkanoidGI>(GetGameInstance());
	GI->Lives = 3;
	GI->Score = 0;
	UGameplayStatics::OpenLevel(this, FName("Arkanoid"));
}

void UMainMenuWidget::ClearRecord()
{
	Cast<UArkanoidGI>(GetGameInstance())->ClearRecord();
	Record_T->SetText(
		FText::FromString(FString::Printf(TEXT("Рекорд: %03d"), Cast<UArkanoidGI>(GetGameInstance())->Record)));
}

void UMainMenuWidget::QuitGame()
{
	UKismetSystemLibrary::QuitGame(this, UGameplayStatics::GetPlayerController(this, 0),
	                               EQuitPreference::Quit, true);
}
