#include "Arkanoid/Public/Framework/ArkanoidPS.h"
#include "Arkanoid/Public/Framework/ArkanoidGameplayClasses.h"
#include "Framework/ArkanoidGI.h"

void AArkanoidPS::BeginPlay()
{
	Super::BeginPlay();

	GameplayClasses->ArkanoidPS = this;

	PlayerScore = GameplayClasses->ArkanoidGI->Score;
}

void AArkanoidPS::ChangePlayerScore(const int32 Amount)
{
	PlayerScore = FMath::Max(PlayerScore + Amount, 0);
	GameplayClasses->ArkanoidGI->Score = PlayerScore;
	OnPlayerScoreChange.Broadcast(PlayerScore);
}
