#include "Arkanoid/Public/Framework/ArkanoidGM.h"
#include "Arkanoid/Public/Framework/ArkanoidGameplayClasses.h"
#include "Arkanoid/Public/Framework/ArkanoidGI.h"
#include "Arkanoid/Public/Framework/ArkanoidHUD.h"
#include "Arkanoid/Public/Framework/ArkanoidPS.h"
#include "Components/AudioComponent.h"
#include "Kismet/GameplayStatics.h"

void AArkanoidGM::BeginPlay()
{
	Super::BeginPlay();

	GameplayClasses->ArkanoidGM = this;
	LevelMusic = UGameplayStatics::SpawnSound2D(this, LevelMusicClass);
}

void AArkanoidGM::SetGamePause()
{
	UGameplayStatics::SetGamePaused(this, !IsPaused());
	GameplayClasses->ArkanoidHUD->SetPause(IsPaused());
}

void AArkanoidGM::GameEnd(bool Win)
{
	bWin = Win;

	UGameplayStatics::PlaySound2D(this, bWin ? SoundWin : SoundDefeat);

	GetWorldTimerManager().SetTimer(Timer, this, &AArkanoidGM::EndGame, 2.f, false);

	if (bWin && GameplayClasses->ArkanoidGI)
	{
		GameplayClasses->ArkanoidGI->Record = FMath::Max(GameplayClasses->ArkanoidGI->Record,
		                                                 GameplayClasses->ArkanoidPS->PlayerScore);
		GameplayClasses->ArkanoidGI->SaveGame();
	}
}

void AArkanoidGM::EndGame()
{
	LevelMusic->Stop();
	GameplayClasses->ArkanoidHUD->EndGame(bWin);
}
