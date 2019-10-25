// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "TronCycleLightTrail.generated.h"

UCLASS()
class TRON_API ATronCycleLightTrail : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ATronCycleLightTrail();

	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable, Category = "Set Active")
		void SetActive(bool bActive);

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "Settings", meta = (DisplayName = "Is Active"))
		bool bIsActive = true;
	UPROPERTY(BlueprintReadOnly, Category = "References", meta = (DisplayName = "Owner Cycle"))
		class ATronCycle * OwnerCycle;
	UPROPERTY(BlueprintReadOnly, Category = "References", meta = (DisplayName = "Game State"))
		class ATronGameState * GameState;
	UPROPERTY(BlueprintReadOnly, Category = "Game", meta = (DisplayName = "Trail Color"))
		FLinearColor TrailColor;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UFUNCTION(BlueprintNativeEvent, Category = "References")
		void GetReferences(bool & Success);

private:

	bool bOwnerCycleTurn = false;
	void OnOwnerCycleTurn(class ATronCycle * cycle, bool bRight);
	void OnOwnerCycleCrash(class ATronCycle * cycle);



};
