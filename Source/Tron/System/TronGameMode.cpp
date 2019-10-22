// Fill out your copyright notice in the Description page of Project Settings.


#include "TronGameMode.h"
#include "Kismet/GameplayStatics.h"

void ATronGameMode::HandleStartingNewPlayer_Implementation(APlayerController* NewPlayer)
{
	Super::HandleStartingNewPlayer_Implementation(NewPlayer);

#if WITH_EDITOR
	SetNumPlayersToStartMatch(GetNumPlayers());
#endif

	TArray<AActor *> findedActors;
	Players.Empty();
	UGameplayStatics::GetAllActorsOfClass(this, APlayerController::StaticClass(), findedActors);
	for (AActor * currentActor : findedActors)
	{
		APlayerController * currentController = Cast<APlayerController>(currentActor);
		if (currentController)
			Players.AddUnique(currentController);
	}
	if (NumPlayersToStartMatch > 0 && Players.Num() >= NumPlayersToStartMatch)
		bReadyToStartMatch = true;
}


void ATronGameMode::SetNumPlayersToStartMatch(int32 num)
{
	NumPlayersToStartMatch = num;
}

void ATronGameMode::StartPlay()
{
#if WITH_EDITOR
	SetNumPlayersToStartMatch(GetNumPlayers());
#endif
	if (NumPlayersToStartMatch > 0 && Players.Num() >= NumPlayersToStartMatch)
		bReadyToStartMatch = true;
	Super::StartPlay();
}

void ATronGameMode::StartMatch()
{
	Super::StartMatch();
}