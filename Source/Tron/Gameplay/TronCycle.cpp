// Fill out your copyright notice in the Description page of Project Settings.


#include "TronCycle.h"


ATronCycle::ATronCycle()
{

	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ATronCycle::BeginPlay()
{
	bool success;
	GetReferences(success);
	Super::BeginPlay();
}

void ATronCycle::GetReferences_Implementation(bool & Success)
{
}

// Called every frame
void ATronCycle::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ATronCycle::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

