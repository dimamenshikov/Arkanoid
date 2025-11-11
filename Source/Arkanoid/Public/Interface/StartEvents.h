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
	virtual void LevelLoad(){};
	virtual void StartGame(){};
};
