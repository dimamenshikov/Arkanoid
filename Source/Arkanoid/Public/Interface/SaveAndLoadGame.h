#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "SaveAndLoadGame.generated.h"

class USaveGame;
struct FDataActor;
class USlotSave;

UINTERFACE()
class USaveAndLoadGame : public UInterface
{
	GENERATED_BODY()
};

class ARKANOID_API ISaveAndLoadGame
{
	GENERATED_BODY()

public:
	virtual USaveGame* Save(USaveGame* BaseSaveObject = nullptr);
	virtual void FindReferences(const USaveGame*& SaveGameObject, const TMap<FString, AActor*>& ExistActors);
	virtual void Load(const USaveGame*& SaveGameObject);
	
	bool LoadingComplete = false;
	bool ReferencesComplete = false;
};

#define CREATE_SAVE_GAME_OBJECT(SaveGameClassName, SaveGameObjectName)													\
auto SaveGameObjectName = Cast<SaveGameClassName>(UGameplayStatics::CreateSaveGameObject(SaveGameClassName::StaticClass()));

#define INIT_SAVE_OBJECT(SaveGameClassName,SaveGameObjectName)															\
SaveGameClassName* SaveGameObjectName = Cast<SaveGameClassName>(BaseSaveObject);										\
if (!SaveGameObjectName) SaveGameObjectName = Cast<SaveGameClassName>(UGameplayStatics::CreateSaveGameObject(SaveGameClassName::StaticClass()));

#define LOAD 0
#define SAVE 0, 0
#define SAVE_VAL(SaveObject, Val) SaveObject->Val = Val
#define LOAD_VAL(SaveObject, Val) Val = SaveObject->Val
#define SELECT(i, j, Macros, ...) Macros

#define SET_VAL_1(SaveObject, Val1, ...) SELECT(__VA_ARGS__, SAVE_VAL(SaveObject, Val1), LOAD_VAL(SaveObject, Val1))
#define SET_VAL_2(SaveObject, Val1, Val2, ...) SET_VAL_1(SaveObject, Val1, __VA_ARGS__); SET_VAL_1(SaveObject, Val2, __VA_ARGS__)
#define SET_VAL_3(SaveObject, Val1, Val2, Val3, ...) SET_VAL_2(SaveObject, Val1, Val2, __VA_ARGS__); SET_VAL_1(SaveObject, Val3, __VA_ARGS__)
#define SET_VAL_4(SaveObject, Val1, Val2, Val3, Val4, ...) SET_VAL_3(SaveObject, Val1, Val2, Val3, __VA_ARGS__); SET_VAL_1(SaveObject, Val4, __VA_ARGS__)
#define SET_VAL_5(SaveObject, Val1, Val2, Val3, Val4, Val5, ...) SET_VAL_4(SaveObject, Val1, Val2, Val3, Val4, __VA_ARGS__); SET_VAL_1(SaveObject, Val5, __VA_ARGS__)
#define SET_VAL_6(SaveObject, Val1, Val2, Val3, Val4, Val5, Val6, ...) SET_VAL_5(SaveObject, Val1, Val2, Val3, Val4, Val5, __VA_ARGS__); SET_VAL_1(SaveObject, Val6, __VA_ARGS__)
#define SET_VAL_7(SaveObject, Val1, Val2, Val3, Val4, Val5, Val6, Val7, ...) SET_VAL_6(SaveObject, Val1, Val2, Val3, Val4, Val5, Val6, __VA_ARGS__); SET_VAL_1(SaveObject, Val7, __VA_ARGS__)
#define SET_VAL_8(SaveObject, Val1, Val2, Val3, Val4, Val5, Val6, Val7, Val8, ...) SET_VAL_7(SaveObject, Val1, Val2, Val3, Val4, Val5, Val6, Val7, __VA_ARGS__); SET_VAL_1(SaveObject, Val8, __VA_ARGS__)
#define SET_VAL_9(SaveObject, Val1, Val2, Val3, Val4, Val5, Val6, Val7, Val8, Val9, ...) SET_VAL_8(SaveObject, Val1, Val2, Val3, Val4, Val5, Val6, Val7, Val8, __VA_ARGS__); SET_VAL_1(SaveObject, Val9, __VA_ARGS__)
#define SET_VAL_10(SaveObject, Val1, Val2, Val3, Val4, Val5, Val6, Val7, Val8, Val9, Val10, ...) SET_VAL_9(SaveObject, Val1, Val2, Val3, Val4, Val5, Val6, Val7, Val8, Val9, __VA_ARGS__); SET_VAL_1(SaveObject, Val10, __VA_ARGS__)
