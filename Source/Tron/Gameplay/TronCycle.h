// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Components/SphereComponent.h"
#include "Runtime/Engine/Classes/Engine/NetSerialization.h"
#include "TronCycle.generated.h"

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

public:	

	virtual void Tick(float DeltaTime) override;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UFUNCTION(BlueprintCallable, Category = "Movement", meta = (DisplayName = "Turn Right"))
		void TurnRight();
	UFUNCTION(BlueprintCallable, Category = "Movement", meta = (DisplayName = "Turn Left"))
		void TurnLeft();
	UFUNCTION(BlueprintPure, Category = "Movement", meta = (DisplayName = "Get Cycle Trails"))
		void GetCycleTrails(TArray<class ATronCycleLightTrail *> & trails);

	FORCEINLINE class USphereComponent* GetSphereComponent() const { return SphereComponent; }
	FORCEINLINE class USceneComponent* GetTrailSource() const { return TrailSource; }

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "Settings|Movement", meta = (DisplayName = "Movement Speed", ClampMin = "0", UIMin = "0"))
		float MovementSpeed = 100;
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "Settings", meta = (DisplayName = "Trail Thickness", ClampMin = "1", UIMin = "1"))
		float TrailThickness = 5;
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "Settings", meta = (DisplayName = "Light Trail Class"))
		TSubclassOf<class ATronCycleLightTrail> LightTrailClass;


		


private:

	UPROPERTY(Category = TronCycle, VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
		class USphereComponent * SphereComponent;
	UPROPERTY(Category = TronCycle, VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
		class USceneComponent * TrailSource;

	UFUNCTION(NetMulticast, Reliable)
		void NetMulticast_TurnRight(FVector turnPoint);
	UFUNCTION(NetMulticast, Reliable)
		void NetMulticast_TurnLeft(FVector turnPoint);

	UFUNCTION(Server, Reliable, WithValidation)
		void Server_TurnRight(FVector turnPoint);
	UFUNCTION(Server, Reliable, WithValidation)
		void Server_TurnLeft(FVector turnPoint);


	void SpawnLightTrail();
	void CycleMovement();
	void TurnCycle(bool bRight, FVector turnPoint);

	TArray<class ATronCycleLightTrail *> CycleTrails;

};
