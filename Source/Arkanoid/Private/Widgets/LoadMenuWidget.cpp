#include "Widgets/LoadMenuWidget.h"
#include "Components/ScrollBox.h"
#include "Components/TextBlock.h"
#include "Framework/ArkanoidGI.h"
#include "Framework/SaveClasses/MainSave.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetTextLibrary.h"
#include "Widgets/SaveSlotWidget.h"

void ULoadMenuWidget::UpdateSaves()
{
	auto Child = Box->GetAllChildren();
	for (auto SaveSlotClass : Child)
	{
		SaveSlotClass->RemoveFromParent();
	}
	if (auto MainSave = Cast<UArkanoidGI>(GetGameInstance())->MainSave)
	{
		for (auto& SlotName : MainSave->Slots)
		{
			const auto Widget = Cast<USaveSlotWidget>(
				CreateWidget(UGameplayStatics::GetPlayerController(GetWorld(), 0), SaveSlotWidgetClass));
			Box->AddChild(Widget);
			Widget->NumberSave->SetText(UKismetTextLibrary::Conv_StringToText(SlotName));
		}
	}
}
