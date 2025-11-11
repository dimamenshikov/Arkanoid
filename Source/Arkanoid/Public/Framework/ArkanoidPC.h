#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "Interface/StartEvents.h"
#include "ArkanoidPC.generated.h"

class APaddle;
class UArkanoidGameplayClasses;

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnStartMove);

struct FInputActionValue;
class UInputAction;
class UInputMappingContext;

UCLASS()
class ARKANOID_API AArkanoidPC : public APlayerController, public IStartEvents
{
	GENERATED_BODY()

public:
	UPROPERTY(EditDefaultsOnly)	UArkanoidGameplayClasses* GameplayClasses = nullptr;

	UPROPERTY(EditDefaultsOnly)	UInputAction* IA_StartMove = nullptr;
	UPROPERTY(EditDefaultsOnly)	UInputAction* IA_Move = nullptr;
	UPROPERTY(EditDefaultsOnly)	UInputAction* IA_Pause = nullptr;
	UPROPERTY(EditDefaultsOnly)	UInputAction* IA_Action = nullptr;

	FOnStartMove OnStartMove;
	
protected:
	virtual void BeginPlay() override;
	
	virtual void LevelLoad() override;
	virtual void StartGame() override;

private:
	UFUNCTION()	void Move(const FInputActionValue& Value);
	UFUNCTION()	void PauseGame();
	UFUNCTION()	void StartMove();

	UPROPERTY(EditDefaultsOnly)	UInputMappingContext* Management = nullptr;

	APaddle* Paddle = nullptr;
};
