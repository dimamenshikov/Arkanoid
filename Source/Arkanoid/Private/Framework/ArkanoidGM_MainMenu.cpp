#include "Arkanoid/Public/Framework/ArkanoidGM_MainMenu.h"
#include "Framework/ArkanoidGI.h"
#include "Kismet/GameplayStatics.h"

void AArkanoidGM_MainMenu::BeginPlay()
{
	Super::BeginPlay();

	auto GI = Cast<UArkanoidGI>(GetGameInstance());
	if (GI->FirstLaunch)
	{
		GI->FirstLaunch = false;
		UGameplayStatics::OpenLevel(this, "Menu", 0);
	}

	UGameplayStatics::PlaySound2D(this, LevelMusic);
}
