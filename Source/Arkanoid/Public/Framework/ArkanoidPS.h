#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "ArkanoidPS.generated.h"

class UInterfaceWidget;
class UArkanoidGameplayClasses;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnPlayerScoreChange, const int32, PlayerScore);

UCLASS(Abstract)
class ARKANOID_API AArkanoidPS : public APlayerState
{
	GENERATED_BODY()

protected:
	UPROPERTY(EditDefaultsOnly)
	UArkanoidGameplayClasses* GameplayClasses = nullptr;

	virtual void BeginPlay() override;

public:
	int32 PlayerScore = 0;
	UPROPERTY()
	FOnPlayerScoreChange OnPlayerScoreChange;

	UFUNCTION()
	void ChangePlayerScore(const int32 Amount);
};
