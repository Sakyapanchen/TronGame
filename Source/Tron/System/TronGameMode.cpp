// Fill out your copyright notice in the Description page of Project Settings.


#include "TronGameMode.h"
#include "Gameplay/TronCycle.h"
#include "GameFramework/PlayerState.h"
#include "GameFramework/PlayerStart.h"
#include "Kismet/GameplayStatics.h"


void ATronGameMode::HandleStartingNewPlayer_Implementation(APlayerController* NewPlayer)
{
	int32 playerIndex = GetNumPlayers() - 1;
	NewPlayer->StartSpot = FindPlayerStart(NewPlayer, FString::FromInt(playerIndex));
	NewPlayer->PlayerState->PlayerId = playerIndex;
#if WITH_EDITOR
	SetNumPlayersToStartMatch(GetNumPlayers());
#endif

	if (MatchStartTimeout <= 0)
	{
		OnMatchStartTimeoutEnded();
		return;
	}
	if (NumPlayersToStartMatch  >= GetNumPlayers())
		this->GetWorld()->GetTimerManager().SetTimer(StartCountdown, this, &ATronGameMode::OnMatchStartTimeoutEnded, MatchStartTimeout, false);
}


void ATronGameMode::SetNumPlayersToStartMatch(int32 num)
{
	NumPlayersToStartMatch = num;
}


void ATronGameMode::BeginPlay()
{
	bool success;
	GetReferences(success);
	Super::BeginPlay();
}

void ATronGameMode::CheckWinConditions()
{
}

void ATronGameMode::OnMatchStartTimeoutEnded()
{
	StartMatch();
}

void ATronGameMode::GetReferences_Implementation(bool & Success)
{

}
