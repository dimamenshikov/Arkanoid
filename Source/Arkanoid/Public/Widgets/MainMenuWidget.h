#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MainMenuWidget.generated.h"

class UButton;
class UTextBlock;

UCLASS(Abstract)
class ARKANOID_API UMainMenuWidget : public UUserWidget
{
	GENERATED_BODY()

protected:
	UPROPERTY(meta = (BindWidget))
	UButton* Start_B = nullptr;
	UPROPERTY(meta = (BindWidget))
	UButton* Quit_B = nullptr;
	UPROPERTY(meta = (BindWidget))
	UButton* ZeroRecord_B = nullptr;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* Record_T = nullptr;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* Start_T = nullptr;
	UPROPERTY(meta = (BindWidget))
	UTextBlock* Quit_T = nullptr;
	UPROPERTY(meta = (BindWidget))
	UTextBlock* ZeroRecord_T = nullptr;

public:
	virtual void NativeOnInitialized() override;
	virtual void NativeConstruct() override;
	UFUNCTION()
	void StartGame();
	UFUNCTION()
	void ClearRecord();
	UFUNCTION()
	void QuitGame();
};
