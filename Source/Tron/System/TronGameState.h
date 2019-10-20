// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameState.h"
#include "TronGameState.generated.h"

/**
 * 
 */
UCLASS()
class TRON_API ATronGameState : public AGameState
{
	GENERATED_BODY()
	
public:

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "Settings", meta = (DisplayName = "Player Colors"))
		TArray<FLinearColor> PlayerColors;
};
