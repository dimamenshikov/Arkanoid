#include "Arkanoid/Public/World/KillZone.h"
#include "Components/BoxComponent.h"

AKillZone::AKillZone()
{
	SceneRoot = CreateDefaultSubobject<USceneComponent>(TEXT("SceneRoot"));
	SetRootComponent(SceneRoot);

	KillZone = CreateDefaultSubobject<UBoxComponent>(TEXT("Kill Zone"));
	KillZone->SetupAttachment(SceneRoot);
}

void AKillZone::NotifyActorBeginOverlap(AActor* OtherActor)
{
	Super::NotifyActorBeginOverlap(OtherActor);

	if (OtherActor != this)
	{
		OtherActor->Destroy();
	}
}
