#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "KillZone.generated.h"

class UBoxComponent;

UCLASS()
class ARKANOID_API AKillZone : public AActor
{
	GENERATED_BODY()

public:
	AKillZone();
	
protected:
	UBoxComponent* KillZone = nullptr;
	USceneComponent* SceneRoot = nullptr;
	
	virtual void NotifyActorBeginOverlap(AActor* OtherActor) override;
};
