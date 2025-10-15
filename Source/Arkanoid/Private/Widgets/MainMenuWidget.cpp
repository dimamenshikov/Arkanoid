#include "Arkanoid/Public/Widgets/MainMenuWidget.h"
#include "Arkanoid/Public/Framework/ArkanoidGI.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"
#include "Kismet/GameplayStatics.h"

void UMainMenuWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	Start_B->OnReleased.AddDynamic(this, &UMainMenuWidget::StartGame);
	Quit_B->OnReleased.AddDynamic(this, &UMainMenuWidget::QuitGame);
	ZeroRecord_B->OnReleased.AddDynamic(this, &UMainMenuWidget::ClearRecord);
}

void UMainMenuWidget::NativeConstruct()
{
	Super::NativeConstruct();

	Record_T->SetText(
		FText::FromString(FString::Printf(TEXT("Рекорд: %03d"), Cast<UArkanoidGI>(GetGameInstance())->Record)));
}

void UMainMenuWidget::StartGame()
{
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
