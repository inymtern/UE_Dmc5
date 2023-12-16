// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "FallToLanded.generated.h"

// This class does not need to be modified.
UINTERFACE()
class UFallToLanded : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class DMCV2_API IFallToLanded
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:

	virtual void Landed();
};
