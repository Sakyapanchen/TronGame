// Fill out your copyright notice in the Description page of Project Settings.


#include "TronCycle.h"

// Sets default values
ATronCycle::ATronCycle()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ATronCycle::BeginPlay()
{
	Super::BeginPlay();
	
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

