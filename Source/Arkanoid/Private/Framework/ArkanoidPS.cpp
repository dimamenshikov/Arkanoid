#include "Arkanoid/Public/Framework/ArkanoidPS.h"
#include "Arkanoid/Public/Framework/ArkanoidGameplayClasses.h"

void AArkanoidPS::BeginPlay()
{
	Super::BeginPlay();

	GameplayClasses->ArkanoidPS = this;
}

void AArkanoidPS::ChangePlayerScore(const int32 Amount)
{
	PlayerScore = FMath::Max(PlayerScore + Amount, 0);
	OnPlayerScoreChange.Broadcast(PlayerScore);
}
