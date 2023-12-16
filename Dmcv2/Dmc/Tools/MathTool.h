// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "MathTool.generated.h"

enum ECustomDir : int;
/**
 * 
 */
UCLASS()
class DMCV2_API UMathTool : public UObject
{
	GENERATED_BODY()
public:
	static ECustomDir CalcRefDirection(const FVector& SelfForward, const FVector& SelfLocation, const FVector& TargetLocation);
};
