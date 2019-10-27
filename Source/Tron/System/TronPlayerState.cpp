// Fill out your copyright notice in the Description page of Project Settings.


#include "TronPlayerState.h"


void ATronPlayerState::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME(ATronPlayerState, PlayerScore);
}

void ATronPlayerState::UpdatePlayerScore(int32 playerScoreIncrement)
{
	if (playerScoreIncrement <= 0)
		return;
	if (this->GetWorld()->GetNetMode() == NM_Client)
	{
		return;
	}
	PlayerScore = PlayerScore + playerScoreIncrement;
	OnRep_PlayerScore();
	ForceNetUpdate();
}

void ATronPlayerState::OnRep_PlayerScore()
{
	OnPlayerScoreChange.Broadcast(this, PlayerScore);
}
