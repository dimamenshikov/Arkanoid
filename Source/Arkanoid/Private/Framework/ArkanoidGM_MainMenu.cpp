#include "Arkanoid/Public/Framework/ArkanoidGM_MainMenu.h"
#include "Kismet/GameplayStatics.h"

void AArkanoidGM_MainMenu::BeginPlay()
{
	Super::BeginPlay();

	UGameplayStatics::PlaySound2D(this, LevelMusic);
}
