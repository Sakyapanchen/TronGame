// Fill out your copyright notice in the Description page of Project Settings.


#include "TronCycleLightTrail.h"

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
}

void ATronCycleLightTrail::GetReferences_Implementation(bool & Success)
{
}


// Called every frame
void ATronCycleLightTrail::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

