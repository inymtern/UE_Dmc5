// Fill out your copyright notice in the Description page of Project Settings.


#include "ForceEdgeFrontHandler.h"

#include "Dmcv2/Dmc/Tools/UPrintTool.h"

void UForceEdgeFrontHandler::Setup(ABaseCharacter* Character)
{
	Super::Setup(Character);
	ActionComponent->FindAction(HandleAction, EWeaponType::ForceEdge, EActionType::N_Front_Attack);
}

void UForceEdgeFrontHandler::Exec()
{
	HandleAction.ActionLifeCycle = EActionLifeCycle::Exec;
	
	HandleAction.Index = 1;
	HandleAction.CurrentAnim = HandleAction.AnimArray[HandleAction.Index];
	ActionComponent->bToggleSignal = !ActionComponent->bToggleSignal;
}

void UForceEdgeFrontHandler::CommonSignal_1()
{
	UUPrintTool::Debug(FString::Printf(TEXT("long : %f"), CurrentPressTime ));
	if(!bReleased && CurrentPressTime >= LongPressTime)
	{
		ActionComponent->FindActionHandlerExec(EWeaponType::ForceEdge,EActionType::S_ForceEdge_Front_Attack_After);
	}else
	{
		HandleAction.Index = 2;
		HandleAction.CurrentAnim = HandleAction.AnimArray[HandleAction.Index];
		ActionComponent->bToggleSignal = !ActionComponent->bToggleSignal;
	}
	
}
