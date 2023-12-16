// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "CollisionTraceTool.generated.h"

/**
 * 
 */
UCLASS()
class DMCV2_API UCollisionTraceTool : public UObject
{
	GENERATED_BODY()
public:
	static bool BoxOverlapTrace(const UWorld* World, TArray<FOverlapResult>& HitResults, const FVector& Location, const FVector& Size, const FRotator& Rotation = FRotator(0,0,0),  bool bIgnoreSelf = true);
};
