// Fill out your copyright notice in the Description page of Project Settings.


#include "UPrintTool.h"

void UUPrintTool::Debug(const FString& Str, const float Duration)
{
	GEngine->AddOnScreenDebugMessage(-1, Duration, FColor::Blue,  Str);
}

void UUPrintTool::Info(const FString& Str, const float Duration)
{
	GEngine->AddOnScreenDebugMessage(-1, Duration, FColor::Green,  Str);
}

void UUPrintTool::Warn(const FString& Str, const float Duration)
{
	GEngine->AddOnScreenDebugMessage(-1, Duration, FColor::Orange,  Str);
}

void UUPrintTool::Error(const FString& Str, const float Duration)
{
	GEngine->AddOnScreenDebugMessage(-1, Duration, FColor::Red,  Str);
}
