#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SaveGame.h"
#include "HUD_S.generated.h"

UCLASS()
class ARKANOID_API UHUD_S : public USaveGame
{
	GENERATED_BODY()

public:
	UPROPERTY()	float Time;
};
