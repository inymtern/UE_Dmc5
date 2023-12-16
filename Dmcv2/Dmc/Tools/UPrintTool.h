// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "UPrintTool.generated.h"

/**
 * 
 */
UCLASS()
class DMCV2_API UUPrintTool : public UObject
{
	GENERATED_BODY()
public:
	static void Debug(const FString& Str, const float Duration = 3.f);
	static void Info(const FString& Str, const float Duration = 3.f);
	static void Warn(const FString& Str, const float Duration = 3.f);
	static void Error(const FString& Str, const float Duration = 3.f);
};
