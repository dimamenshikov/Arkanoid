#include "Interface/SaveAndLoadGame.h"

USaveGame* ISaveAndLoadGame::Save(USaveGame* BaseSaveObject)
{
	return BaseSaveObject;
}

void ISaveAndLoadGame::FindReferences(const USaveGame*& SaveGameObject, const TMap<FString, AActor*>& ExistActors)
{
	ReferencesComplete = true;
}

void ISaveAndLoadGame::Load(const USaveGame*& SaveGameObject)
{
	LoadingComplete = true;
}
