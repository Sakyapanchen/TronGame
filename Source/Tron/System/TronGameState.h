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
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "Settings", meta = (DisplayName = "Score To Win", ClampMin = "1", UIMin = "1"))
		int32 ScoreToWin = 3;
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "Settings", meta = (DisplayName = "Match Start Timeout", ClampMin = "0", UIMin = "0"))
		float MatchStartTimeout = 2;
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "Settings", meta = (DisplayName = "Match End Timeout", ClampMin = "1", UIMin = "1"))
		float MatchEndTimeout = 2;
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "Settings", meta = (DisplayName = "After Round Timeout", ClampMin = "1", UIMin = "1"))
		float AfterRoundTimeout = 2;
};
