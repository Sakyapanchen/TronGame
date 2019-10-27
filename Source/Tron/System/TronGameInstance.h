// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintPlatformLibrary.h"
#include "TronGameInstance.generated.h"

/**
 * 
 */
UCLASS()
class TRON_API UTronGameInstance : public UPlatformGameInstance
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintCallable, Category = "Game")
		void SetNumPlayersToStartMatch(int32 num);

	UPROPERTY(BlueprintReadOnly, Category = "Game")
		int32 NumPlayersToStartMatch = -1;
	
};
