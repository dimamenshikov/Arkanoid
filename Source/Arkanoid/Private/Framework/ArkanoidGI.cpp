#include "Arkanoid/Public/Framework/ArkanoidGI.h"
#include "Arkanoid/Public/Framework/ArkanoidGameplayClasses.h"
#include "Arkanoid/Public/Framework/SaveClasses/SaveSlot.h"
#include "GameFramework/SaveGame.h"
#include "Kismet/GameplayStatics.h"

void UArkanoidGI::Init()
{
	Super::Init();

	GameplayClasses->ArkanoidGI = this;

	LoadGame();
}

void UArkanoidGI::SaveGame()
{
	if (!SaveSlot)
	{
		SaveSlot = Cast<USaveSlot>(UGameplayStatics::LoadGameFromSlot(SlotName, 0));
	}
	if (!IsValid(SaveSlot))
	{
		SaveSlot = Cast<USaveSlot>(UGameplayStatics::CreateSaveGameObject(USaveSlot::StaticClass()));
	}

	if (SaveSlot)
	{
		SaveSlot->PlayerScore = Record;
		UGameplayStatics::SaveGameToSlot(SaveSlot, SlotName, 0);
	}
}

void UArkanoidGI::LoadGame()
{
	SaveSlot = Cast<USaveSlot>(UGameplayStatics::LoadGameFromSlot(SlotName, 0));

	if (SaveSlot)
	{
		Record = SaveSlot->PlayerScore;
	}
}

void UArkanoidGI::ClearRecord()
{
	Record = 0;
	if (UGameplayStatics::DoesSaveGameExist(SlotName, 0))
	{
		UGameplayStatics::DeleteGameInSlot(SlotName, 0);
	}
}
