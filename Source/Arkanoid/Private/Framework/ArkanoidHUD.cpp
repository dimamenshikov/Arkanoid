#include "Arkanoid/Public/Framework/ArkanoidHUD.h"
#include "Arkanoid/Public/Framework/ArkanoidGameplayClasses.h"
#include "Arkanoid/Public/Framework/ArkanoidGI.h"
#include "Arkanoid/Public/Framework/ArkanoidPS.h"
#include "Arkanoid/Public/Widgets/InterfaceWidget.h"
#include "Arkanoid/Public/Widgets/PauseWidget.h"
#include "Blueprint/UserWidget.h"
#include "Components/TextBlock.h"
#include "Kismet/GameplayStatics.h"

void AArkanoidHUD::BeginPlay()
{
	Super::BeginPlay();

	GameplayClasses->ArkanoidHUD = this;

	Interface = Cast<UInterfaceWidget>(CreateWidget(PlayerOwner, InterfaceClass));
	Interface->AddToViewport();

	GetWorldTimerManager().SetTimer(Timer, this, &AArkanoidHUD::LevelLoad, 0.1f, false);
}

void AArkanoidHUD::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	Time += DeltaSeconds;
	UpdateTime();
}

void AArkanoidHUD::EndGame(bool bWin)
{
	bPause = false;

	if (!Pause)
	{
		Pause = Cast<UPauseWidget>(CreateWidget(PlayerOwner, PauseClass));
	}

	Pause->Continue_T->SetText(FText::FromString(TEXT("Начать заново")));
	Pause->EndGame_T->SetText(FText::FromString(bWin ? TEXT("Победа") : TEXT("Поражение")));
	Pause->EndGame_T->SetColorAndOpacity(
		bWin ? FSlateColor(FLinearColor::Green) : FSlateColor(FLinearColor::Red));

	SetPause(true);
	UGameplayStatics::SetGamePaused(this, !UGameplayStatics::GetPlayerController(this, 0)->IsPaused());
}

void AArkanoidHUD::SetPause(const bool bPauseGame)
{
	if (!Pause)
	{
		Pause = Cast<UPauseWidget>(CreateWidget(PlayerOwner, PauseClass));
	}

	if (bPauseGame)
	{
		Pause->AddToViewport();
		UGameplayStatics::GetPlayerController(this, 0)->SetInputMode(FInputModeGameAndUI());
	}
	else
	{
		Pause->RemoveFromParent();
		UGameplayStatics::GetPlayerController(this, 0)->SetInputMode(FInputModeGameOnly());
	}

	UGameplayStatics::GetPlayerController(this, 0)->SetShowMouseCursor(bPauseGame);
}

void AArkanoidHUD::LevelLoad()
{
	GameplayClasses->ArkanoidPS->OnPlayerScoreChange.AddDynamic(this, &AArkanoidHUD::UpdateScore);

	UGameplayStatics::GetPlayerController(this, 0)->SetShowMouseCursor(false);
	UGameplayStatics::GetPlayerController(this, 0)->SetInputMode(FInputModeGameOnly());

	Interface->UpdateScore(GameplayClasses->ArkanoidPS->PlayerScore, GameplayClasses->ArkanoidGI->Record);
}

void AArkanoidHUD::UpdateScore(const int32 NewScore)
{
	Interface->UpdateScore(NewScore);
}

void AArkanoidHUD::UpdateTime()
{
	Interface->UpdateTime(Time);
}
