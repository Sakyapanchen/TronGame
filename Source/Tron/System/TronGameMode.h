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

	virtual void HandleStartingNewPlayer_Implementation(APlayerController* NewPlayer) override;

	virtual void StartMatch() override;

	virtual bool PlayerCanRestart_Implementation(APlayerController* Player) override;

	UFUNCTION(BlueprintCallable, Category = "Game")
		void CycleCrashMessage(ATronCycle * cycle);
	UFUNCTION(BlueprintCallable, Category = "Game")
		void StartNewRound();


	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "Settings", meta = (DisplayName = "Match Map Name"))
		FString MatchMapName = "GameMap";
	UPROPERTY(BlueprintReadOnly, Category = "Game")
		int32 NumPlayersToStartMatch = -1;
	UPROPERTY(BlueprintReadOnly, meta = (DisplayName = "Score To Win"))
		int32 ScoreToWin = -1;
	UPROPERTY(BlueprintReadOnly, meta = (DisplayName = "Match Start Timeout"))
		float MatchStartTimeout = 0;
	UPROPERTY(BlueprintReadOnly, meta = (DisplayName = "Match End Timeout"))
		float MatchEndTimeout = 0;
	UPROPERTY(BlueprintReadOnly, meta = (DisplayName = "After Round Timeout"))
		float AfterRoundTimeout = 0;
	UPROPERTY(BlueprintReadOnly, Category = "Game")
		bool bReadyToStartMatch;
	UPROPERTY(BlueprintReadOnly, Category = "Game")
		int32 CurrentRound = -1;

protected:

	virtual void BeginPlay() override;

	UFUNCTION(BlueprintNativeEvent, Category = "References")
		void GetReferences(bool & Success);

private:

	void CheckWinConditions();
	void OnMatchStartTimeoutEnded();
	void OnMatchEndTimeoutEnded();
	void OnRoundTimeoutEnded();
	void RefreshPlayers();
	void FetchGameStateData();
	class ATronGameState * GameState;
	class UTronGameInstance * GameInstance;
	TArray<class AActor *> PlayerStarts;
	FTimerHandle StartCountdown;
	FTimerHandle AfterReoundCountdown;
	FTimerHandle EndCountdown;
	int32 CrashedCyclesNum = 0;
};
