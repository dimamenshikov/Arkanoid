#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "ArkanoidGI.generated.h"

class UArkanoidGameplayClasses;
class USaveSlot;

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnLevelLoad);

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnStartGame);

UCLASS(Abstract)
class ARKANOID_API UArkanoidGI : public UGameInstance
{
	GENERATED_BODY()

private:
	FString SlotName = "Main";

protected:
	UPROPERTY(EditDefaultsOnly)
	UArkanoidGameplayClasses* GameplayClasses = nullptr;

	virtual void Init() override;

public:
	FOnLevelLoad OnLevelLoad;
	FOnStartGame OnStartGame;

	UPROPERTY()
	USaveSlot* SaveSlot = nullptr;
	int32 Record = 0;

	void SaveGame();
	void LoadGame();
	void ClearRecord();
};
