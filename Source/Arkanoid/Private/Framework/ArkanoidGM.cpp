#include "Arkanoid/Public/Framework/ArkanoidGM.h"
#include "EngineUtils.h"
#include "Arkanoid/Public/Framework/ArkanoidGameplayClasses.h"
#include "Arkanoid/Public/Framework/ArkanoidGI.h"
#include "Arkanoid/Public/Framework/ArkanoidHUD.h"
#include "Arkanoid/Public/Framework/ArkanoidPS.h"
#include "Components/AudioComponent.h"
#include "Framework/SaveClasses/MainSave.h"
#include "Kismet/GameplayStatics.h"
#include "World/Block.h"

AArkanoidGM::AArkanoidGM()
{
	Music = CreateDefaultSubobject<UAudioComponent>(TEXT("LevelMusic"));
	Music->SetAutoActivate(false);
}

void AArkanoidGM::BeginPlay()
{
	Super::BeginPlay();

	GameplayClasses->ArkanoidGM = this;
}

void AArkanoidGM::LevelLoad()
{
	Music->Play();
}

void AArkanoidGM::StartGame()
{
	for (TActorIterator<ABlock> Block(GetWorld()); Block; ++Block)
	{
		Blocks.Add(*Block);
		Block->OnDestroyed.AddDynamic(this, &AArkanoidGM::DestroyBlock);
	}
}

void AArkanoidGM::DestroyBlock(AActor* Destroyed)
{
	Blocks.Remove(Cast<ABlock>(Destroyed));
	if (Blocks.IsEmpty())
	{
		GameEnd(true);
	}
}

void AArkanoidGM::SetGamePause()
{
	UGameplayStatics::SetGamePaused(this, !IsPaused());
	GameplayClasses->ArkanoidHUD->SetPause(IsPaused());
	GameplayClasses->ArkanoidGI->Pause(IsPaused());
}

void AArkanoidGM::GameEnd(const bool Win)
{
	GameplayClasses->ArkanoidGI->CanSaveGame = false;
	
	auto EndGame_1 = [this, Win]()-> void
	{
		UGameplayStatics::PlaySound2D(this, Win ? SoundWin : SoundDefeat);
		Music->Deactivate();
	};
	FTimerHandle Timer_1;
	GetWorldTimerManager().SetTimer(Timer_1, EndGame_1, 1.f, false);

	auto EndGame_2 = [this, Win]()-> void
	{
		if (!Win || (Win && GameplayClasses->ArkanoidGI->Levels.Last() == UGameplayStatics::GetCurrentLevelName(this)))
		{
			if (Win && GameplayClasses->ArkanoidGI->Record < GameplayClasses->ArkanoidPS->PlayerScore)
			{
				GameplayClasses->ArkanoidGI->Record = GameplayClasses->ArkanoidPS->PlayerScore;
				if (GameplayClasses->ArkanoidGI->MainSave)
				{
					GameplayClasses->ArkanoidGI->MainSave->Record = GameplayClasses->ArkanoidGI->Record;
					UGameplayStatics::SaveGameToSlot(GameplayClasses->ArkanoidGI->MainSave, "Main", 0);
				}
			}
			GameplayClasses->ArkanoidHUD->EndGame(Win);
			SetGamePause();
		}
		else
		{
			int32 Index;
			GameplayClasses->ArkanoidGI->Levels.Find(UGameplayStatics::GetCurrentLevelName(this), Index);
			UGameplayStatics::OpenLevel(this, FName(GameplayClasses->ArkanoidGI->Levels[Index + 1]));
		}
	};
	FTimerHandle Timer_2;
	GetWorldTimerManager().SetTimer(Timer_2, EndGame_2, 3.f, false);
}
