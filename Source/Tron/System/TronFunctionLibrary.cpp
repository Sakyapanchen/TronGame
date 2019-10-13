// Fill out your copyright notice in the Description page of Project Settings.


#include "TronFunctionLibrary.h"

bool UTronFunctionLibrary::IsEditor()
{
#if WITH_EDITOR
	return true;
#endif
	return false;
}
