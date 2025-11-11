#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "PauseWidget.generated.h"

class ULoadMenuWidget;
class UWidgetSwitcher;
class AArkanoidHUD;
class UTextBlock;
class UButton;
class UArkanoidGameplayClasses;

UCLASS(Abstract)
class ARKANOID_API UPauseWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	UPROPERTY(meta = (BindWidget))	UTextBlock* EndGame_T = nullptr;
	UPROPERTY(meta = (BindWidget))	UTextBlock* Continue_T = nullptr;
	
	AArkanoidHUD* Owner = nullptr;

protected:
	virtual void NativeOnInitialized() override;
	virtual void NativeConstruct() override;

private:
	UFUNCTION()	void Back();
	UFUNCTION()	void Continue();
	UFUNCTION()	void InMainMenu();
	UFUNCTION()	void Quit();
	UFUNCTION()	void Load();
	UFUNCTION()	void Save();

	UPROPERTY(meta = (BindWidget))	UWidgetSwitcher* Switcher = nullptr;
	UPROPERTY(meta = (BindWidget))	ULoadMenuWidget* LoadMenu = nullptr;

	UPROPERTY(meta = (BindWidget))	UButton* Continue_B = nullptr;
	UPROPERTY(meta = (BindWidget))	UButton* Back_B = nullptr;
	UPROPERTY(meta = (BindWidget))	UButton* Save_B = nullptr;
	UPROPERTY(meta = (BindWidget))	UButton* Load_B = nullptr;
	UPROPERTY(meta = (BindWidget))	UButton* Quit_B = nullptr;
	UPROPERTY(meta = (BindWidget))	UButton* InMainMenu_B = nullptr;

	UPROPERTY(meta = (BindWidget))	UTextBlock* Record_T = nullptr;
	UPROPERTY(meta = (BindWidget))	UTextBlock* Score_T = nullptr;
	UPROPERTY(meta = (BindWidget))	UTextBlock* Save_T = nullptr;
	UPROPERTY(meta = (BindWidget))	UTextBlock* Quit_T = nullptr;
	UPROPERTY(meta = (BindWidget))	UTextBlock* InMainMenu_T = nullptr;
};
