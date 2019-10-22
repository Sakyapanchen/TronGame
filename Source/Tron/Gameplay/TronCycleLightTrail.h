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

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UFUNCTION(BlueprintNativeEvent, Category = "References")
		void GetReferences(bool & Success);

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable, Category = "Set Active")
		void SetActive(bool bActive);

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "Settings", meta = (DisplayName = "Is Active"))
		bool bIsActive = true;


};
