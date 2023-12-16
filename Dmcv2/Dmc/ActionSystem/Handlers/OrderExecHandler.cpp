// Fill out your copyright notice in the Description page of Project Settings.


#include "OrderExecHandler.h"

void UOrderExecHandler::Pre_1()
{
	Super::Pre_1();
}

void UOrderExecHandler::Exec()
{
	Super::Exec();
	HandleAction.Index++;
	HandleAction.CurrentAnim = HandleAction.AnimArray[HandleAction.Index];
	ActionComponent->bToggleSignal = !ActionComponent->bToggleSignal;
}

void UOrderExecHandler::After_1()
{
	Super::After_1();
	HandleAction.Index++;
	HandleAction.CurrentAnim = HandleAction.AnimArray[HandleAction.Index];
	ActionComponent->bToggleSignal = !ActionComponent->bToggleSignal;
}
