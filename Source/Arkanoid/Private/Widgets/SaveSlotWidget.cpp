#include "Widgets/SaveSlotWidget.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"
#include "Framework/ArkanoidGameplayClasses.h"
#include "Framework/ArkanoidGI.h"
#include "Kismet/KismetTextLibrary.h"

void USaveSlotWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	Load_B->OnReleased.AddDynamic(this, &USaveSlotWidget::Load);
	Delete_B->OnReleased.AddDynamic(this, &USaveSlotWidget::Delete);
}

void USaveSlotWidget::Load()
{
	GameplayClasses->ArkanoidGI->LoadGame(UKismetTextLibrary::Conv_TextToString(NumberSave->GetText()));
}

void USaveSlotWidget::Delete()
{
	GameplayClasses->ArkanoidGI->DeleteSlot(UKismetTextLibrary::Conv_TextToString(NumberSave->GetText()));
	RemoveFromParent();
}
