#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintAsyncActionBase.h"
#include "AsyncSave.generated.h"

class USaveGame;

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FAsyncSaveOutputPin);

/**
 * Async Save
 */
UCLASS()
class ASYNCSAVELOAD_API UAsyncSave : public UBlueprintAsyncActionBase
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintAssignable)
	FAsyncSaveOutputPin Completed;

	UPROPERTY(BlueprintAssignable)
	FAsyncSaveOutputPin Failed;

	UFUNCTION(BlueprintCallable, meta=(BlueprintInternalUseOnly = "true", WorldContext = "WorldContextObject"), Category="AsyncSaveLoad")
	static UAsyncSave* AsyncSave(const UObject* WorldContextObject, USaveGame* SaveGameInstance, const FString& SlotName, const int32 UserIndex);

	virtual void Activate() override;

private:
	const UObject* WorldContextObject;
	USaveGame* SaveGameInstance;
	FString SlotName;
	int32 UserIndex;
};
