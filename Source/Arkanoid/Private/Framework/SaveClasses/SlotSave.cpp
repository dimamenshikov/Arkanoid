#include "Arkanoid/Public/Framework/SaveClasses/SlotSave.h"

int32 USlotSave::FindName(const FString& Name)
{
	for (int32 i = 0; i < DataSaveActor.Num(); ++i)
	{
		if (Name == DataSaveActor[i].Name)
		{
			return i;
		}
	}

	return -1;
}
