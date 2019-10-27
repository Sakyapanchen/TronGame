// Fill out your copyright notice in the Description page of Project Settings.


#include "TronCycleLightTrail.h"
#include "Kismet/GameplayStatics.h"
#include "System/TronGameState.h"
#include "Gameplay/TronCycle.h"

// Sets default values
ATronCycleLightTrail::ATronCycleLightTrail()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}


void ATronCycleLightTrail::BeginPlay()
{
	bool success;
	GetReferences(success);
	Super::BeginPlay();
	if (OwnerCycle)
	{
		OwnerCycle->OnCycleCrash.AddDynamic(this, &ATronCycleLightTrail::OnOwnerCycleCrash);
		OwnerCycle->OnCycleTurn.AddDynamic(this, &ATronCycleLightTrail::OnOwnerCycleTurn);
		if (GameState)
		{
			TArray<FLinearColor> Colors = GameState->PlayerColors;
			int32 playerID = OwnerCycle->PlayerID;
			if (Colors.IsValidIndex(playerID))
				TrailColor = Colors[playerID];
		}
	}
	CreateProceduralMesh(success);
}

void ATronCycleLightTrail::UpdateProceduralMesh_Implementation(bool & bResult)
{
}

void ATronCycleLightTrail::CreateProceduralMesh_Implementation(bool & bResult)
{
}


void ATronCycleLightTrail::GetReferences_Implementation(bool & Success)
{
	AGameStateBase * gameState = UGameplayStatics::GetGameState(this);
	if (gameState)
		GameState = Cast<ATronGameState>(gameState);
	if (GetOwner())
		OwnerCycle = Cast<ATronCycle>(GetOwner());
}


void ATronCycleLightTrail::Tick(float DeltaTime)
{
	bool success;
	if (bIsActive)
		UpdateProceduralMesh(success);
	Super::Tick(DeltaTime);
	if (bOwnerCycleTurn && bIsActive)
		SetActive(false);
}

void ATronCycleLightTrail::SetActive(bool bActive)
{
	bIsActive = bActive;
}

void ATronCycleLightTrail::OnOwnerCycleTurn(ATronCycle * cycle, bool bRight)
{
	bOwnerCycleTurn = true;
}

void ATronCycleLightTrail::OnOwnerCycleCrash(ATronCycle * cycle)
{
	SetActive(false);
}


