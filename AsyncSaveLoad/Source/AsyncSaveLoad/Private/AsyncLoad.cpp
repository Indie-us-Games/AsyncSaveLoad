#include "AsyncLoad.h"

#include "Engine/Classes/GameFramework/SaveGame.h"
#include "Engine/Classes/Kismet/GameplayStatics.h"

UAsyncLoad* UAsyncLoad::AsyncLoad(const UObject* WorldContextObject, USaveGame* SaveGameInstance, const FString& SlotName, const int32 UserIndex)
{
	UAsyncLoad* Node = NewObject<UAsyncLoad>();
	Node->WorldContextObject = WorldContextObject;
	Node->SaveGameInstance = SaveGameInstance;
	Node->SlotName = SlotName;
	Node->UserIndex = UserIndex;
	return Node;
}

void UAsyncLoad::Activate()
{
	static bool bAsyncActive = false;

	if (!bAsyncActive)
	{
		FFunctionGraphTask::CreateAndDispatchWhenReady([this]()
		{
			bAsyncActive = true;
			SaveGameInstance = UGameplayStatics::LoadGameFromSlot(SlotName, UserIndex);
			Completed.Broadcast(SaveGameInstance);
			bAsyncActive = false;
		}, TStatId(), NULL, ENamedThreads::AnyBackgroundThreadNormalTask);
	}
	else
	{
		Failed.Broadcast(SaveGameInstance);
	}
}
