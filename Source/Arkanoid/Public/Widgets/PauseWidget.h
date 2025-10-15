#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "PauseWidget.generated.h"

class UTextBlock;
class UButton;
class UArkanoidGameplayClasses;

UCLASS(Abstract)
class ARKANOID_API UPauseWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	UPROPERTY(EditDefaultsOnly)
	UArkanoidGameplayClasses* GameplayClasses = nullptr;

	UPROPERTY(meta = (BindWidget))
	UButton* Continue_B = nullptr;
	UPROPERTY(meta = (BindWidget))
	UButton* Quit_B = nullptr;
	UPROPERTY(meta = (BindWidget))
	UButton* InMainMenu_B = nullptr;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* Record_T = nullptr;
	UPROPERTY(meta = (BindWidget))
	UTextBlock* EndGame_T = nullptr;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* Continue_T = nullptr;
	UPROPERTY(meta = (BindWidget))
	UTextBlock* Quit_T = nullptr;
	UPROPERTY(meta = (BindWidget))
	UTextBlock* InMainMenu_T = nullptr;
	
	virtual void NativeOnInitialized() override;
	virtual void NativeConstruct() override;
	UFUNCTION() void Continue();
	UFUNCTION() void InMainMenu();
	UFUNCTION() void Quit();
};
