#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintAsyncActionBase.h"
#include "AsyncLoad.generated.h"

class USaveGame;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FAsyncLoadOutputPin, USaveGame*, SaveGame);

/**
 * ASync Load
 */
UCLASS()
class ASYNCSAVELOAD_API UAsyncLoad : public UBlueprintAsyncActionBase
{
	GENERATED_BODY()
	
public:
	UPROPERTY(BlueprintAssignable)
	FAsyncLoadOutputPin Completed;

	UPROPERTY(BlueprintAssignable)
	FAsyncLoadOutputPin Failed;

	UFUNCTION(BlueprintCallable, meta=(BlueprintInternalUseOnly = "true", WorldContext = "WorldContextObject"), Category="AsyncSaveLoad")
	static UAsyncLoad* AsyncLoad(const UObject* WorldContextObject, USaveGame* SaveGameInstance, const FString& SlotName, const int32 UserIndex);

	virtual void Activate() override;

private:
	const UObject* WorldContextObject;
	USaveGame* SaveGameInstance;
	FString SlotName;
	int32 UserIndex;
};
