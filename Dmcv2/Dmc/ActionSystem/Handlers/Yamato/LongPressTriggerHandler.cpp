// Fill out your copyright notice in the Description page of Project Settings.


#include "LongPressTriggerHandler.h"

void ULongPressTriggerHandler::Exec()
{
	
	HandleAction.ActionLifeCycle = EActionLifeCycle::Exec;
}

void ULongPressTriggerHandler::Pre_2()
{
	if(!bReleased)
	{
		bCrossPre2 = true;
		HandleAction.Index = 1;
		HandleAction.CurrentAnim = HandleAction.AnimArray[HandleAction.Index];
		ActionComponent->bToggleSignal = !ActionComponent->bToggleSignal;
	}
}

void ULongPressTriggerHandler::Pre_3()
{
	if(!bReleased)
	{
		HandleAction.Index = 2;
		HandleAction.CurrentAnim = HandleAction.AnimArray[HandleAction.Index];
		ActionComponent->bToggleSignal = !ActionComponent->bToggleSignal;
	}
}

void ULongPressTriggerHandler::FinishReleased()
{
	if(bCrossPre2)
	{
		bCrossPre2 = false;
		HandleAction.Index = 2;
		HandleAction.CurrentAnim = HandleAction.AnimArray[HandleAction.Index];
		ActionComponent->bToggleSignal = !ActionComponent->bToggleSignal;
	}
}
