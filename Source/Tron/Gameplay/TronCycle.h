// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Components/SphereComponent.h"
#include "Runtime/Engine/Classes/Engine/NetSerialization.h"
#include "TronCycle.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FCycleCrashResult, ATronCycle *, Cycle);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FCycleTurnResult, ATronCycle *, Cycle, bool, bRight);

UCLASS()
class TRON_API ATronCycle : public APawn
{
	GENERATED_BODY()

public:

	ATronCycle(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

protected:

	virtual void BeginPlay() override;

	UFUNCTION(BlueprintNativeEvent, Category = "References")
		void GetReferences(bool & Success);
	UFUNCTION(BlueprintNativeEvent, Category = "Game", meta = (DisplayName = "On Player ID Recieved"))
		void OnPlayerIdRecieved(int32 playerId);

public:	

	virtual void Tick(float DeltaTime) override;

	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UFUNCTION(BlueprintCallable, Category = "Movement", meta = (DisplayName = "Turn Right"))
		void TurnRight();
	UFUNCTION(BlueprintCallable, Category = "Movement", meta = (DisplayName = "Turn Left"))
		void TurnLeft();
	UFUNCTION(BlueprintCallable, Category = "Movement", meta = (DisplayName = "Enable Movement"))
		void EnableMovement(bool bEnabled);
	UFUNCTION(BlueprintPure, Category = "Movement", meta = (DisplayName = "Get Cycle Trails"))
		void GetCycleTrails(TArray<class ATronCycleLightTrail *> & trails);
	UFUNCTION(BlueprintCallable, Category = "Game", meta = (DisplayName = "Clear Trails"))
		void ClearTrails();
	UFUNCTION(BlueprintCallable, Category = "Game", meta = (DisplayName = "Cycle Overlap"))
		void CycleOverlap(AActor * actor);
	UFUNCTION(BlueprintCallable, Category = "Game", meta = (DisplayName = "Cycle Hit"))
		void CycleHit(AActor * actor);
	UFUNCTION(BlueprintPure, Category = "Movement", meta = (DisplayName = "Get Trail Source Point"))
		void GetTrailSourcePoint(FVector & point);

	FORCEINLINE class USphereComponent* GetSphereComponent() const { return SphereComponent; }

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "Settings|Movement", meta = (DisplayName = "Movement Speed", ClampMin = "0", UIMin = "0"))
		float MovementSpeed = 100;
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "Settings", meta = (DisplayName = "Trail Thickness", ClampMin = "1", UIMin = "1"))
		float TrailThickness = 5;
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "Settings", meta = (DisplayName = "Light Trail Class"))
		TSubclassOf<class ATronCycleLightTrail> LightTrailClass;
	UPROPERTY(BlueprintReadOnly, Category = "Movement", meta = (DisplayName = "Is Movement"))
		bool bIsMovement = false;
	UPROPERTY(BlueprintReadOnly, Category = "Game", meta = (DisplayName = "Is Crashed"))
		bool bIsCrashed = false;
	UPROPERTY(BlueprintReadOnly, Category = "Game", meta = (DisplayName = "Player ID"))
		int32 PlayerID = -1;

	UPROPERTY(BlueprintReadOnly, Category = "References", meta = (DisplayName = "Game Mode"))
		class ATronGameMode * GameMode;
	UPROPERTY(BlueprintReadOnly, Category = "References", meta = (DisplayName = "Game State"))
		class ATronGameState * GameState;

	UPROPERTY(BlueprintAssignable, Category = "Game", meta = (DisplayName = "On Cycle Crash"))
		FCycleCrashResult OnCycleCrash;
	UPROPERTY(BlueprintAssignable, Category = "Game", meta = (DisplayName = "On Cycle Turn"))
		FCycleTurnResult OnCycleTurn;

private:

	UPROPERTY(Category = TronCycle, VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
		class USphereComponent * SphereComponent;

	UFUNCTION(NetMulticast, Reliable)
		void NetMulticast_TurnRight(FVector turnPoint);
	UFUNCTION(NetMulticast, Reliable)
		void NetMulticast_TurnLeft(FVector turnPoint);
	UFUNCTION(NetMulticast, Reliable)
		void NetMulticast_EnableMovement(bool bEnabled);
	UFUNCTION(NetMulticast, Reliable)
		void NetMulticast_PlayerIdRecieved(int32 inPlayerId);

	UFUNCTION(Server, Reliable, WithValidation)
		void Server_TurnRight(FVector turnPoint);
	UFUNCTION(Server, Reliable, WithValidation)
		void Server_TurnLeft(FVector turnPoint);


	void SpawnLightTrail();
	void CycleMovement();
	void CycleCrash();
	void TryGetPlayerId();
	void TurnCycle(bool bRight, FVector turnPoint);

	TArray<class ATronCycleLightTrail *> CycleTrails;

};
