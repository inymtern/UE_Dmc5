// Fill out your copyright notice in the Description page of Project Settings.


#include "ManyClickManyTriggeredHandler.h"

#include "Dmcv2/Dmc/Tools/UPrintTool.h"

bool UManyClickManyTriggeredHandler::Trigger()
{
	if(!bSaved)
	{
		CurrentTriggerCount++;
		bSaved = true;
		return true;
	}
	return false;
}

void UManyClickManyTriggeredHandler::EnterNext()
{
	HandleAction.Index = 2;
	HandleAction.CurrentAnim = HandleAction.AnimArray[2];
	ActionComponent->bToggleSignal = !ActionComponent->bToggleSignal;
}

bool UManyClickManyTriggeredHandler::BeforeEnter()
{
	if(ActionComponent->CurrentHandler == this)
	{
		return false;
	}
		
	if(ActionComponent->CurrentHandler->HandleAction.ActionLifeCycle == EActionLifeCycle::After_2 && ActionComponent->CurrentHandler->Break(this))
	{
		BreakEnterHandle();
		return true;
	}
	return false;
}

void UManyClickManyTriggeredHandler::Exec()
{
	Super::Exec();
	HandleAction.Index = 1;
	HandleAction.CurrentAnim = HandleAction.AnimArray[1];
	ActionComponent->bToggleSignal = !ActionComponent->bToggleSignal;
}

void UManyClickManyTriggeredHandler::After_1()
{
	if(!bSaved || CurrentTriggerCount >= MaxTriggerCount)
	{
		Super::After_1();
		EnterNext();
	}else
	{
		bSaved = false;
		ActionComponent->bToggleSignal = !ActionComponent->bToggleSignal;
	}
}
