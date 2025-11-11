#include "Arkanoid/Public/Framework/ArkanoidHUD.h"
#include "Arkanoid/Public/Framework/ArkanoidGameplayClasses.h"
#include "Arkanoid/Public/Framework/ArkanoidGI.h"
#include "Arkanoid/Public/Framework/ArkanoidPS.h"
#include "Arkanoid/Public/Widgets/InterfaceWidget.h"
#include "Arkanoid/Public/Widgets/PauseWidget.h"
#include "Blueprint/UserWidget.h"
#include "Components/TextBlock.h"
#include "Framework/ArkanoidPC.h"
#include "Framework/Paddle.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetTextLibrary.h"
#include "SaveClasses/HUD_S.h"

void AArkanoidHUD::BeginPlay()
{
	Super::BeginPlay();

	GameplayClasses->ArkanoidHUD = this;
}

void AArkanoidHUD::LevelLoad()
{
	Interface = Cast<UInterfaceWidget>(CreateWidget(GameplayClasses->ArkanoidPC, InterfaceClass));
	Interface->AddToViewport();
	Interface->UpdateScore(GameplayClasses->ArkanoidPS->PlayerScore, GameplayClasses->ArkanoidGI->Record);

	Pause = Cast<UPauseWidget>(CreateWidget(GameplayClasses->ArkanoidPC, PauseClass));
	Pause->Owner = this;

	GameplayClasses->ArkanoidPC->SetShowMouseCursor(false);
	GameplayClasses->ArkanoidPC->SetInputMode(FInputModeGameOnly());

	GameplayClasses->ArkanoidPS->OnPlayerScoreChange.AddDynamic(this, &AArkanoidHUD::UpdateScore);

	GameplayClasses->ArkanoidP->OnLifeChange.AddDynamic(this, &AArkanoidHUD::UpdateLives);
	ShowTime();
	UpdateLives(GameplayClasses->ArkanoidGI->Lives);
}

void AArkanoidHUD::StartGame()
{
	GetWorldTimerManager().SetTimer(Timer, this, &AArkanoidHUD::UpdateTime, GetWorld()->DeltaTimeSeconds, true);
}

void AArkanoidHUD::UpdateTime()
{
	Time += GetWorld()->DeltaTimeSeconds;
	Interface->UpdateTime(Time);
}

void AArkanoidHUD::EndGame(bool bWin)
{
	GetWorldTimerManager().ClearTimer(Timer);
	bPause = false;

	Pause->Continue_T->SetText(FText::FromString(TEXT("Начать заново")));
	Pause->EndGame_T->SetText(FText::FromString(bWin ? TEXT("Победа") : TEXT("Поражение")));
	Pause->EndGame_T->SetColorAndOpacity(
		bWin ? FSlateColor(FLinearColor::Green) : FSlateColor(FLinearColor::Red));

	SetPause(true);
}

void AArkanoidHUD::SetPause(const bool bPauseGame)
{
	if (bPauseGame)
	{
		Pause->AddToViewport();
		GameplayClasses->ArkanoidPC->SetInputMode(FInputModeGameAndUI());
	}
	else
	{
		Pause->RemoveFromParent();
		GameplayClasses->ArkanoidPC->SetInputMode(FInputModeGameOnly());
	}

	GameplayClasses->ArkanoidPC->SetShowMouseCursor(bPauseGame);
}

void AArkanoidHUD::ShowTime()
{
	if (Interface->Number == 0)
	{
		Interface->Launch_T->SetVisibility(ESlateVisibility::Hidden);
		return;
	}
	Interface->Launch_T->SetText(UKismetTextLibrary::Conv_IntToText(Interface->Number--));

	FTimerHandle TimerTemp;
	GetWorldTimerManager().SetTimer(TimerTemp, this, &AArkanoidHUD::ShowTime, 1.0f, false);
}

void AArkanoidHUD::UpdateScore(const int32 NewScore)
{
	Interface->UpdateScore(NewScore);
}

void AArkanoidHUD::UpdateLives(const int32 NewLives)
{
	Interface->UpdateLives(NewLives);
}

USaveGame* AArkanoidHUD::Save(USaveGame* BaseSaveObject)
{
	INIT_SAVE_OBJECT(UHUD_S, HUD_S);
	SET_VAL_1(HUD_S, Time, SAVE);
	return ISaveAndLoadGame::Save(HUD_S);
}

void AArkanoidHUD::Load(const USaveGame*& SaveGameObject)
{
	ISaveAndLoadGame::Load(SaveGameObject);
	auto HUD_S = Cast<UHUD_S>(SaveGameObject);
	SET_VAL_1(HUD_S, Time, LOAD);
}
