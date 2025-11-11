#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "LoadMenuWidget.generated.h"

class UScrollBox;
class UVerticalBox;
class UArkanoidGameplayClasses;

UCLASS()
class ARKANOID_API ULoadMenuWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	UPROPERTY(EditDefaultsOnly)
	UArkanoidGameplayClasses* GameplayClasses = nullptr;
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UUserWidget> SaveSlotWidgetClass;

	UPROPERTY(meta=(BindWidget))
	UScrollBox* Box;

	void UpdateSaves();
};
