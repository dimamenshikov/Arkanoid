#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "StartEvents.generated.h"

UINTERFACE()
class UStartEvents : public UInterface
{
	GENERATED_BODY()
};

class ARKANOID_API IStartEvents
{
	GENERATED_BODY()

public:
	void BindStartEvents(AActor* Self, bool bLevelLoad, bool bStartGame);
	UFUNCTION()	virtual void LevelLoad(){};
	UFUNCTION()	virtual void StartGame(){};
};
