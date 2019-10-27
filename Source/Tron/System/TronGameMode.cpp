// Fill out your copyright notice in the Description page of Project Settings.


#include "TronGameMode.h"
#include "Gameplay/TronCycle.h"
#include "System/TronGameState.h"
#include "System/TronPlayerState.h"
#include "System/TronGameInstance.h"
#include "GameFramework/PlayerStart.h"
#include "Kismet/GameplayStatics.h"


void ATronGameMode::HandleStartingNewPlayer_Implementation(APlayerController* NewPlayer)
{
	UWorld * world = this->GetWorld();
	if (!world)
		return;
	bool success;
	GetReferences(success);
	FetchGameStateData();
	FString currentMap = UGameplayStatics::GetCurrentLevelName(this, true);
	if (currentMap != MatchMapName)
		return;	
	int32 playerIndex = GetNumPlayers() - 1;
	FString playerId = FString::FromInt(playerIndex);
	NewPlayer->StartSpot = FindPlayerStart(NewPlayer, playerId);
	NewPlayer->PlayerState->PlayerId = playerIndex;
	NewPlayer->PlayerState->SetPlayerName("Player" + playerId);
#if WITH_EDITOR
	if(NumPlayersToStartMatch <= 0)
		NumPlayersToStartMatch = GetNumPlayers();
#endif

	if (MatchStartTimeout <= 0)
	{
		OnMatchStartTimeoutEnded();
		return;
	}
	if (NumPlayersToStartMatch  >= 1 && GetNumPlayers() >= NumPlayersToStartMatch)
		world->GetTimerManager().SetTimer(StartCountdown, this, &ATronGameMode::OnMatchStartTimeoutEnded, MatchStartTimeout, false);
}

void ATronGameMode::StartMatch()
{
	Super::StartMatch();
	CurrentRound = 1;
}

bool ATronGameMode::PlayerCanRestart_Implementation(APlayerController * Player)
{
	if (Player == nullptr || Player->IsPendingKillPending())
	{
		return false;
	}
	return Player->CanRestartPlayer();
}

void ATronGameMode::CycleCrashMessage(ATronCycle * cycle)
{
	CrashedCyclesNum++;
	if (CrashedCyclesNum >= GetNumPlayers() - 1)
		CheckWinConditions();
}

void ATronGameMode::StartNewRound()
{
	for (FConstPlayerControllerIterator Iterator = GetWorld()->GetPlayerControllerIterator(); Iterator; ++Iterator)
	{
		APlayerController* PlayerController = Iterator->Get();
		if(PlayerController->GetPawn())
			PlayerController->GetPawn()->Destroy(false, true);
		if (PlayerController && (PlayerController->GetPawn() == nullptr) && PlayerCanRestart(PlayerController))
		{
			RestartPlayer(PlayerController);
		}
	}
	CurrentRound++;
}

void ATronGameMode::CheckWinConditions()
{
	for (FConstPawnIterator Iterator = this->GetWorld()->GetPawnIterator(); Iterator; ++Iterator)
	{
		APawn* pawn = Iterator->Get();
		if (pawn)
		{
			ATronCycle * cycle = Cast<ATronCycle>(pawn);
			if (cycle && cycle->GetPlayerState() && !cycle->bIsCrashed)
			{
				ATronPlayerState * playerState = Cast<ATronPlayerState>(cycle->GetPlayerState());
				playerState->UpdatePlayerScore(1);
				cycle->EnableMovement(false);
				this->GetWorld()->GetTimerManager().SetTimer(AfterReoundCountdown, this, &ATronGameMode::OnRoundTimeoutEnded, AfterRoundTimeout, false);
				if (playerState->PlayerScore >= ScoreToWin)
				{
					this->GetWorld()->GetTimerManager().ClearAllTimersForObject(this);
					this->GetWorld()->GetTimerManager().SetTimer(EndCountdown, this, &ATronGameMode::OnMatchEndTimeoutEnded, MatchEndTimeout, false);
					return;
				}
				return;
			}
		}
	}
}


void ATronGameMode::BeginPlay()
{
	bool success;
	GetReferences(success);
	Super::BeginPlay();
	FetchGameStateData();
}

void ATronGameMode::OnMatchStartTimeoutEnded()
{
	StartMatch();
}

void ATronGameMode::OnMatchEndTimeoutEnded()
{
	RefreshPlayers();
	RestartGame();
}

void ATronGameMode::OnRoundTimeoutEnded()
{
	CrashedCyclesNum = 0;
	StartNewRound();
}

void ATronGameMode::RefreshPlayers()
{
		for (FConstPlayerControllerIterator Iterator = GetWorld()->GetPlayerControllerIterator(); Iterator; ++Iterator)
	{
		APlayerController* PlayerController = Iterator->Get();
		if (PlayerController->PlayerState)
		{
			ATronPlayerState * playerState = Cast<ATronPlayerState>(PlayerController->PlayerState);
			playerState->UpdatePlayerScore(playerState->PlayerScore * -1);
		}
		if (PlayerController->GetPawn())
			PlayerController->GetPawn()->Destroy(false, true);
	}
}

void ATronGameMode::FetchGameStateData()
{
	if (GameInstance)
		NumPlayersToStartMatch = GameInstance->NumPlayersToStartMatch;
	if (!GameState)
		return;
	ScoreToWin = GameState->ScoreToWin;
	MatchStartTimeout = GameState->MatchStartTimeout;
	MatchEndTimeout = GameState->MatchEndTimeout;
	AfterRoundTimeout = GameState->AfterRoundTimeout;
}

void ATronGameMode::GetReferences_Implementation(bool & Success)
{
	if (!GameInstance)
	{
		if (UGameplayStatics::GetGameInstance(this))
			GameInstance = Cast<UTronGameInstance>(UGameplayStatics::GetGameInstance(this));
	}
	if (!GameState)
	{
		if (UGameplayStatics::GetGameState(this))
			GameState = Cast<ATronGameState>(UGameplayStatics::GetGameState(this));
	}	
}
