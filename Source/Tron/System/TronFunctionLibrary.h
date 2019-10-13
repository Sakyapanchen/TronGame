// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "TronFunctionLibrary.generated.h"

/**
 * 
 */
UCLASS()
class TRON_API UTronFunctionLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

	UFUNCTION(BlueprintPure, Category = "Utility|Tron Function Library")
		static bool IsEditor();
	
};
