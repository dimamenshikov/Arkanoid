#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "ArkanoidGameplayClasses.generated.h"

class APaddle;
class AArkanoidGM;
class AArkanoidPS;
class AArkanoidHUD;
class AArkanoidGM_MainMenu;
class UArkanoidGI;

UCLASS()
class ARKANOID_API UArkanoidGameplayClasses : public UDataAsset
{
	GENERATED_BODY()

public:
	UArkanoidGI* ArkanoidGI = nullptr;
	AArkanoidGM* ArkanoidGM = nullptr;
	AArkanoidHUD* ArkanoidHUD = nullptr;
	AArkanoidPS* ArkanoidPS = nullptr;
	APaddle* Paddle = nullptr;
};
