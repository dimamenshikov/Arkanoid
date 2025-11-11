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

public:
	UFUNCTION()	void ChangePlayerScore(const int32 Amount);
	
	UPROPERTY()	FOnPlayerScoreChange OnPlayerScoreChange;
	
	int32 PlayerScore = 0;
	
protected:
	virtual void BeginPlay() override;

	UPROPERTY(EditDefaultsOnly)	UArkanoidGameplayClasses* GameplayClasses = nullptr;
};
