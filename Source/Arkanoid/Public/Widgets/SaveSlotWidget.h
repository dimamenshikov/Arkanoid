#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "SaveSlotWidget.generated.h"

class UArkanoidGameplayClasses;
class UTextBlock;
class UButton;

UCLASS()
class ARKANOID_API USaveSlotWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	UPROPERTY(EditDefaultsOnly)	UArkanoidGameplayClasses* GameplayClasses = nullptr;
	
	UPROPERTY(meta = (BindWidget))	UTextBlock* NumberSave = nullptr;

protected:
	virtual void NativeOnInitialized() override;
	
private:
	UFUNCTION()	void Load();
	UFUNCTION()	void Delete();
	
	UPROPERTY(meta = (BindWidget))	UButton* Load_B = nullptr;
	UPROPERTY(meta = (BindWidget))	UButton* Delete_B = nullptr;
};
