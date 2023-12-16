// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "AttackTraceInterface.generated.h"

// This class does not need to be modified.
UINTERFACE()
class UAttackTraceInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class DMCV2_API IAttackTraceInterface
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	void AttackTrace(UWorld* World, FVector Size, FVector Location, FRotator Rotator);
};
