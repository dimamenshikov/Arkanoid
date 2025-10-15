#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "InterfaceWidget.generated.h"

class UTextBlock;
class UArkanoidGameplayClasses;

UCLASS(Abstract)
class ARKANOID_API UInterfaceWidget : public UUserWidget
{
	GENERATED_BODY()

protected:
	UPROPERTY(EditDefaultsOnly)
	UArkanoidGameplayClasses* GameplayClasses = nullptr;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* CurrentScore = nullptr;
	UPROPERTY(meta = (BindWidget))
	UTextBlock* GameTime = nullptr;
	UPROPERTY(meta = (BindWidget))
	UTextBlock* Record_T = nullptr;

public:
	void UpdateScore(const int32 NewScore, const int32 NewRecord = -1);
	void UpdateTime(const float Time) const;
};
