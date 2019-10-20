// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "TronCycle.generated.h"

UCLASS()
class TRON_API ATronCycle : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ATronCycle();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UFUNCTION(BlueprintNativeEvent, Category = "References")
		void GetReferences(bool & Success);

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "Settings|Movement", meta = (DisplayName = "Movement Speed", ClampMin = "0", UIMin = "0"))
		float MovementSpeed = 100;
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "Settings", meta = (DisplayName = "Trail Thickness", ClampMin = "1", UIMin = "1"))
		float TrailThickness = 5;

};
