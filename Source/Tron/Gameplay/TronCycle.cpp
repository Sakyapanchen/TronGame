// Fill out your copyright notice in the Description page of Project Settings.


#include "TronCycle.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/PlayerState.h"
#include "TronCycleLightTrail.h"
#include "Engine/EngineTypes.h"

ATronCycle::ATronCycle(const FObjectInitializer& ObjectInitializer): Super(ObjectInitializer)
{

	PrimaryActorTick.bCanEverTick = true;
	SphereComponent = CreateDefaultSubobject<USphereComponent>(FName("TronCycleSphere"));
	SphereComponent->InitSphereRadius(7.f);
	SphereComponent->SetCollisionProfileName(UCollisionProfile::Pawn_ProfileName);
	RootComponent = SphereComponent;
}

// Called when the game starts or when spawned
void ATronCycle::BeginPlay()
{
	bool success;
	GetReferences(success);
	Super::BeginPlay();
	if(bIsMovement)
		SpawnLightTrail();
}

void ATronCycle::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);
	if (EndPlayReason == EEndPlayReason::Destroyed)
		ClearTrails();
}

void ATronCycle::GetReferences_Implementation(bool & Success)
{

}

// Called every frame
void ATronCycle::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	TryGetPlayerId();
	CycleMovement();
}

// Called to bind functionality to input
void ATronCycle::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void ATronCycle::TurnRight()
{
	TurnCycle(true, GetActorLocation());
	ENetMode netMode = this->GetWorld()->GetNetMode();
	if (netMode == NM_Client)
	{
		Server_TurnRight(GetActorLocation());
	}
	NetMulticast_TurnRight(GetActorLocation());
}

void ATronCycle::TurnLeft()
{
	TurnCycle(false, GetActorLocation());
	ENetMode netMode = this->GetWorld()->GetNetMode();
	if (netMode == NM_Client)
	{
		Server_TurnLeft(GetActorLocation());
	}
	NetMulticast_TurnLeft(GetActorLocation());
}

void ATronCycle::EnableMovement(bool bEnabled)
{
	bIsMovement = bEnabled;
	ENetMode netMode = this->GetWorld()->GetNetMode();
	if (netMode == NM_Client)
	{
		return;
	}
	NetMulticast_EnableMovement(bEnabled);
}

void ATronCycle::GetCycleTrails(TArray<class ATronCycleLightTrail*>& trails)
{
	trails = CycleTrails;
}

void ATronCycle::ClearTrails()
{
	for (ATronCycleLightTrail * currentTail : CycleTrails)
	{
		currentTail -> Destroy();
	}
	CycleTrails.Empty();
}

void ATronCycle::GetTrailSourcePoint(FVector & point)
{
	point = (GetActorForwardVector() * -1 * SphereComponent->GetScaledSphereRadius()) + GetActorLocation();
}

void ATronCycle::NetMulticast_TurnRight_Implementation(FVector turnPoint)
{
	if (IsLocallyControlled())
		return;
	TurnCycle(true, turnPoint);
}

void ATronCycle::NetMulticast_TurnLeft_Implementation(FVector turnPoint)
{
	if (IsLocallyControlled())
		return;
	TurnCycle(false, turnPoint);
}

void ATronCycle::NetMulticast_EnableMovement_Implementation(bool bEnabled)
{
	bIsMovement = bEnabled;
	if (bIsMovement)
		SpawnLightTrail();
}

void ATronCycle::NetMulticast_PlayerIdRecieved_Implementation(int32 inPlayerId)
{
	PlayerID = inPlayerId;
	ENetMode netMode = this->GetWorld()->GetNetMode();
	if (netMode != NM_Client)
		EnableMovement(true);
}

void ATronCycle::Server_TurnRight_Implementation(FVector turnPoint)
{
	NetMulticast_TurnRight(turnPoint);
}
bool ATronCycle::Server_TurnRight_Validate(FVector turnPoint)
{
	return true;
}

void ATronCycle::Server_TurnLeft_Implementation(FVector turnPoint)
{
	NetMulticast_TurnLeft(turnPoint);
}
bool ATronCycle::Server_TurnLeft_Validate(FVector turnPoint)
{
	return true;
}

void ATronCycle::SpawnLightTrail()
{
	UWorld* CurrentWorld = this->GetWorld();
	if (!CurrentWorld)
		return;
	if (!LightTrailClass)
		return;	
	ESpawnActorCollisionHandlingMethod collisionHandlindOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
	FVector sourcePoint;
	GetTrailSourcePoint(sourcePoint);
	FTransform spawnTransform = FTransform(GetActorRotation(), sourcePoint, FVector(1.f,1.f,1.f));
	ATronCycleLightTrail * currentActor = CurrentWorld->SpawnActorDeferred<ATronCycleLightTrail>(LightTrailClass, spawnTransform, this, nullptr, collisionHandlindOverride);
	if (!currentActor)
		return;
	UGameplayStatics::FinishSpawningActor(currentActor, spawnTransform);
	CycleTrails.AddUnique(currentActor);
}

void ATronCycle::CycleMovement()
{
	if (!bIsMovement)
		return;
	FHitResult * hitResult = nullptr;
	FVector deltaLocation = (UGameplayStatics::GetWorldDeltaSeconds(this) * MovementSpeed) * GetActorForwardVector();
	AddActorWorldOffset(deltaLocation, true, hitResult, ETeleportType::None);
}

void ATronCycle::TryGetPlayerId()
{
	if (PlayerID >= 0)
		return;
	ENetMode netMode = this->GetWorld()->GetNetMode();
	if (netMode == NM_Client)
		return;
	if(!this->GetPlayerState())
		return;
	NetMulticast_PlayerIdRecieved(this->GetPlayerState()->PlayerId);
}

void ATronCycle::TurnCycle(bool bRight, FVector turnPoint)
{
	FRotator deltaRotation = FRotator(0, -90, 0);
	if(bRight)
		deltaRotation = FRotator(0, 90, 0);
	FHitResult * hitResult = nullptr;
	SetActorLocation(turnPoint, false, hitResult, ETeleportType::TeleportPhysics);
	AddActorWorldRotation(deltaRotation, false, hitResult, ETeleportType::TeleportPhysics);
	SpawnLightTrail();
}
