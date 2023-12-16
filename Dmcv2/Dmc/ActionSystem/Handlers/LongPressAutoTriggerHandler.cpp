// Fill out your copyright notice in the Description page of Project Settings.


#include "LongPressAutoTriggerHandler.h"

#include "Dmcv2/Dmc/Tools/UPrintTool.h"

void ULongPressAutoTriggerHandler::Pre_1()
{
	Super::Pre_1();
}

void ULongPressAutoTriggerHandler::SelfEnterHandle()
{
	Super::SelfEnterHandle();
	bReleased = false;
	CurrentPressTime = 0.f;
}

void ULongPressAutoTriggerHandler::BreakEnterHandle()
{
	Super::BreakEnterHandle();
	bReleased = false;
	CurrentPressTime = 0.f;
}

void ULongPressAutoTriggerHandler::Exec()
{
	Super::Exec();
	UUPrintTool::Info(FString::Printf(TEXT("long press time = %f"), CurrentPressTime));
	if(!bReleased && CurrentPressTime >= LongPressTime)
	{
		HandleAction.Index = 1;
		HandleAction.CurrentAnim = HandleAction.AnimArray[HandleAction.Index];
		ActionComponent->bToggleSignal = !ActionComponent->bToggleSignal;
	}
}

bool ULongPressAutoTriggerHandler::Break(UBaseActionHandler* SourceActionHandler)
{
	bReleased = false;
	CurrentPressTime = 0.f;
	return Super::Break(SourceActionHandler);
}
