#include "AsyncSave.h"

#include "Engine/Classes/GameFramework/SaveGame.h"
#include "Engine/Classes/Kismet/GameplayStatics.h"

UAsyncSave* UAsyncSave::AsyncSave(const UObject* WorldContextObject, USaveGame* SaveGameInstance, const FString& SlotName, const int32 UserIndex)
{
	UAsyncSave* Node = NewObject<UAsyncSave>();
	Node->WorldContextObject = WorldContextObject;
	Node->SaveGameInstance = SaveGameInstance;
	Node->SlotName = SlotName;
	Node->UserIndex = UserIndex;
	return Node;
}

void UAsyncSave::Activate()
{
	static bool bAsyncActive = false;

	if (!bAsyncActive)
	{
		FFunctionGraphTask::CreateAndDispatchWhenReady([this]()
		{
			bAsyncActive = true;
			UGameplayStatics::SaveGameToSlot(SaveGameInstance, SlotName, UserIndex);
			Completed.Broadcast();
			bAsyncActive = false;
		}, TStatId(), NULL, ENamedThreads::AnyBackgroundThreadNormalTask);
	}
	else
	{
		Failed.Broadcast();
	}
}
