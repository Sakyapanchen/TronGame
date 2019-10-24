// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameMode.h"
#include "TronGameMode.generated.h"

/**
 * 
 */
UCLASS()
class TRON_API ATronGameMode : public AGameMode
{
	GENERATED_BODY()


public:

	UFUNCTION(BlueprintCallable, Category = "Game")
		void SetNumPlayersToStartMatch(int32 num);

	UPROPERTY(BlueprintReadOnly, Category = "Game")
		int32 NumPlayersToStartMatch = -1;

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "Settings", meta = (DisplayName = "Match Start Timeout", ClampMin = "0", UIMin = "0"))
		float MatchStartTimeout = 2;

	UPROPERTY(BlueprintReadOnly, Category = "Game")
		bool bReadyToStartMatch;

	UPROPERTY(BlueprintReadOnly, Category = "Game")
	TArray<APlayerController *> Players;

	virtual void HandleStartingNewPlayer_Implementation(APlayerController* NewPlayer) override;

protected:

	virtual void BeginPlay() override;

	UFUNCTION(BlueprintNativeEvent, Category = "References")
		void GetReferences(bool & Success);

private:

	void UpdateControllersList();
	void OnMatchStartTimeoutEnded();
	TArray<class AActor *> PlayerStarts;	
	FTimerHandle StartCountdown;
};
