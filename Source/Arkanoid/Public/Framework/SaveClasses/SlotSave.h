#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SaveGame.h"
#include "SlotSave.generated.h"

USTRUCT()
struct FDataActor
{
	GENERATED_BODY()

	UPROPERTY()	FString Name;
	UPROPERTY()	FTransform Transform;
	UPROPERTY()	TSubclassOf<AActor> Class;

	bool Exist = false;
};

UCLASS()
class ARKANOID_API USlotSave : public USaveGame
{
	GENERATED_BODY()

public:
	UPROPERTY()	TArray<FDataActor> DataSaveActor;
	UPROPERTY()	FName LevelName;
	UPROPERTY()	int32 PlayerScore = 0;
	UPROPERTY()	int32 Record = 0;
	UPROPERTY()	int32 Lives;

	int32 FindName(const FString& Name);
};
