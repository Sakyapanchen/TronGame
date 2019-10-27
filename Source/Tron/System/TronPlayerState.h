// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "Net/UnrealNetwork.h"
#include "TronPlayerState.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FPlayerScoreChangeResult, ATronPlayerState *, PlayerState, int32, Score);

UCLASS()
class TRON_API ATronPlayerState : public APlayerState
{
	GENERATED_BODY()
	
public:

	virtual void GetLifetimeReplicatedProps(TArray< FLifetimeProperty > & OutLifetimeProps) const override;

	UFUNCTION(BlueprintCallable, Category = "Game")
		void UpdatePlayerScore(int32 playerScoreIncrement);

	UPROPERTY(replicatedUsing = OnRep_PlayerScore, BlueprintReadOnly, Category = "Game")
		int32 PlayerScore;

	UPROPERTY(BlueprintAssignable, Category = "Game")
		FPlayerScoreChangeResult OnPlayerScoreChange;

private:

	UFUNCTION()
		virtual void OnRep_PlayerScore();

};
