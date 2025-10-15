#include "Interface/StartEvents.h"
#include "Framework/ArkanoidGI.h"

void IStartEvents::BindStartEvents(AActor* Self, bool bLevelLoad, bool bStartGame)
{
	const auto GI = Cast<UArkanoidGI>(Self->GetWorld()->GetGameInstance());
	if (bLevelLoad)
	{
		GI->OnLevelLoad.AddDynamic(this, &IStartEvents::LevelLoad);
	}
	if (bStartGame)
	{
		GI->OnStartGame.AddDynamic(this, &IStartEvents::StartGame);
	}
}
