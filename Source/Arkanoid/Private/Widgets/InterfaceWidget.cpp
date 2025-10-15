#include "Arkanoid/Public/Widgets/InterfaceWidget.h"
#include "Components/TextBlock.h"

void UInterfaceWidget::UpdateScore(const int32 NewScore, const int32 NewRecord)
{
	FString ScoreString = FString::Printf(TEXT("Счёт: %03d"), NewScore);
	CurrentScore->SetText(FText::FromString(ScoreString));

	if (NewRecord != -1)
	{
		ScoreString = FString::Printf(TEXT("Рекорд: %03d"), NewRecord);
		Record_T->SetText(FText::FromString(ScoreString));
	}
}

void UInterfaceWidget::UpdateTime(const float Time) const
{
	const int32 Minutes = static_cast<int32>(Time) / 60;
	const int32 Seconds = static_cast<int32>(Time) % 60;
	const int32 Milliseconds = static_cast<int32>((Time - static_cast<int32>(Time)) * 100);

	const FString TimeString = FString::Printf(TEXT("%02d: %02d: %02d"), Minutes, Seconds, Milliseconds);
	GameTime->SetText(FText::FromString(TimeString));
}
