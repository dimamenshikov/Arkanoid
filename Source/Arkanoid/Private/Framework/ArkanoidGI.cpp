#include "Arkanoid/Public/Framework/ArkanoidGI.h"
#include "EngineUtils.h"
#include "Arkanoid/Public/Framework/ArkanoidGameplayClasses.h"
#include "Arkanoid/Public/Framework/SaveClasses/SlotSave.h"
#include "Framework/ArkanoidPS.h"
#include "Framework/Paddle.h"
#include "Framework/SaveClasses/MainSave.h"
#include "GameFramework/SaveGame.h"
#include "Interface/SaveAndLoadGame.h"
#include "Interface/StartEvents.h"
#include "Kismet/GameplayStatics.h"

void UArkanoidGI::Init()
{
	Super::Init();

	GameplayClasses->ArkanoidGI = this;

	Score = 0;

	MainSave = Cast<UMainSave>(UGameplayStatics::LoadGameFromSlot("Main", 0));
	if (MainSave)
	{
		Record = MainSave->Record;
	}
}

void UArkanoidGI::LoadComplete(const float LoadTime, const FString& MapName)
{
	CanSaveGame = true;
	CanSaveTime = true;
	StartGame = false;
	LevelLoad = false;

	if (LoadingSlot != " ")
	{
		LoadLevel();
	}

	for (TActorIterator<AActor> Actor(GetWorld()); Actor; ++Actor)
	{
		if (const auto StartEventActor = Cast<IStartEvents>(*Actor))
		{
			StartEventActor->LevelLoad();
		}
	}
	LevelLoad = true;

	auto GameStart = [this]()-> void
	{
		for (TActorIterator<AActor> Actor(GetWorld()); Actor; ++Actor)
		{
			if (const auto StartEventActor = Cast<IStartEvents>(*Actor))
			{
				StartEventActor->StartGame();
			}
		}
		StartGame = true;
	};
	GetTimerManager().SetTimer(Timer, GameStart, 3.0f, false);
}

void UArkanoidGI::LoadGame(const FString& SlotName)
{
	SlotSave = Cast<USlotSave>(UGameplayStatics::LoadGameFromSlot(SlotName, 0));
	if (!SlotSave) return;

	LoadingSlot = SlotName;
	UGameplayStatics::OpenLevel(GetWorld(), SlotSave->LevelName);
}

void UArkanoidGI::LoadLevel()
{
	TMap<FString, AActor*> ExistReferences;
	TMap<FString, ISaveAndLoadGame*> SaveActors;

	Lives = SlotSave->Lives;


	for (TActorIterator<AActor> Actor(GetWorld()); Actor; ++Actor)
	{
		ExistReferences.Add(Actor->GetName(), *Actor);
		if (auto SaveActor = Cast<ISaveAndLoadGame>(*Actor))
		{
			if (const int32 Index = SlotSave->FindName(Actor->GetName()); Index != -1)
			{
				Actor->SetActorTransform(SlotSave->DataSaveActor[Index].Transform);
				SlotSave->DataSaveActor[Index].Exist = true;
				SaveActors.Add(SlotSave->DataSaveActor[Index].Name, SaveActor);
			}
			else
			{
				Actor->Destroy();
			}
		}
	}

	for (auto& Item : SlotSave->DataSaveActor)
	{
		if (!Item.Exist)
		{
			Item.Exist = true;
			Item.Transform.SetScale3D(FVector(1.f, 1.f, 1.f));
			if (auto SaveActor = GetWorld()->SpawnActor<AActor>(Item.Class, Item.Transform))
			{
				ExistReferences.Add(Item.Name, SaveActor);
				SaveActors.Add(Item.Name, Cast<ISaveAndLoadGame>(SaveActor));
			}
		}
	}

	TArray<const USaveGame*> SaveGames;
	for (auto& Item : SaveActors)
	{
		if (const USaveGame* SaveGameObject = UGameplayStatics::LoadGameFromSlot(LoadingSlot + Item.Key, 0))
		{
			SaveGames.Add(SaveGameObject);
			Item.Value->FindReferences(SaveGameObject, ExistReferences);
		}
	}

	int32 Index = 0;
	for (auto& Item : SaveActors)
	{
		if (SaveGames[Index])
		{
			Item.Value->Load(SaveGames[Index]);
			++Index;
		}
	}
	GameplayClasses->ArkanoidPS->PlayerScore = SlotSave->PlayerScore;
	LoadingSlot = " ";
}

void UArkanoidGI::SaveGame()
{
	if (!CanSaveGame || !CanSaveTime) return;

	CanSaveTime = false;

	SlotSave = Cast<USlotSave>(UGameplayStatics::CreateSaveGameObject(USlotSave::StaticClass()));

	SlotSave->Lives = Lives;
	SlotSave->Record = Record;
	SlotSave->PlayerScore = GameplayClasses->ArkanoidPS->PlayerScore;

	const FString SlotName = FDateTime::Now().ToString();
	for (TActorIterator<AActor> Actor(GetWorld()); Actor; ++Actor)
	{
		if (const auto SaveActor = Cast<ISaveAndLoadGame>(*Actor))
		{
			UGameplayStatics::SaveGameToSlot(SaveActor->Save(), SlotName + Actor->GetName(), 0);
			SlotSave->DataSaveActor.Add(FDataActor(Actor->GetName(), Actor->GetActorTransform(),
			                                       Actor->GetClass(), false));
		}
	}

	SlotSave->LevelName = FName(UGameplayStatics::GetCurrentLevelName(GetWorld()));
	UGameplayStatics::SaveGameToSlot(SlotSave, SlotName, 0);

	if (!MainSave)
	{
		MainSave = Cast<UMainSave>(UGameplayStatics::CreateSaveGameObject(UMainSave::StaticClass()));
	}

	MainSave->Slots.Add(SlotName);
	UGameplayStatics::SaveGameToSlot(MainSave, "Main", 0);
}

void UArkanoidGI::ClearRecord()
{
	Record = 0;

	if (MainSave)
	{
		MainSave->Record = 0;
		UGameplayStatics::SaveGameToSlot(MainSave, "Main", 0);
	}
}

void UArkanoidGI::DeleteSlot(const FString& SlotName)
{
	if (auto Slot = Cast<USlotSave>(UGameplayStatics::LoadGameFromSlot(SlotName, 0)); MainSave && Slot)
	{
		for (auto& ActorSave : Slot->DataSaveActor)
		{
			UGameplayStatics::DeleteGameInSlot(SlotName + ActorSave.Name, 0);
		}
		UGameplayStatics::DeleteGameInSlot(SlotName, 0);
		MainSave->Slots.Remove(SlotName);
		UGameplayStatics::SaveGameToSlot(MainSave, "Main", 0);
	}
}

void UArkanoidGI::Pause(bool Pause)
{
	if (!Pause && !CanSaveTime && !TimerCanSaveActive)
	{
		TimerCanSaveActive = true;
		FTimerHandle TimerCanSave;
		GetTimerManager().SetTimer(TimerCanSave, [this]()-> void
		{
			CanSaveTime = true;
			TimerCanSaveActive = false;
		}, 2.0f, false);
	}
}

void UArkanoidGI::AddLives(const int32 AddLives)
{
	Lives = FMath::Max(0, Lives + AddLives);
	GameplayClasses->ArkanoidP->OnLifeChange.Broadcast(Lives);
}
