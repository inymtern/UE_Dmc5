// Fill out your copyright notice in the Description page of Project Settings.


#include "ForceEdgeComboAHandler.h"

#include "ForceEdgeComboA1Handler.h"
#include "Dmcv2/Dmc/ActionSystem/Handlers/ManyClickManyTriggeredHandler.h"

void UForceEdgeComboAHandler::Setup(ABaseCharacter* Character)
{
	Super::Setup(Character);
	ActionComponent->FindAction(HandleAction, EWeaponType::ForceEdge, EActionType::N_Combo_A);
}

bool UForceEdgeComboAHandler::BeforeEnter()
{
	if(ActionComponent->CurrentHandler == this)
	{
		SelfEnterHandle();
		return true;
	}
	UBaseActionHandler* BaseActionHandler = ActionComponent->CurrentHandler;
	const FAction CurrentHandleAction = ActionComponent->CurrentHandler->HandleAction;

	if(CurrentHandleAction.ActionType == EActionType::N_Combo_A1 &&
		CurrentHandleAction.WeaponType == EWeaponType::ForceEdge &&
		CurrentHandleAction.ActionLifeCycle < EActionLifeCycle::After_1)
	{
		UForceEdgeComboA1Handler* ForceEdgeComboA1Handler = Cast<UForceEdgeComboA1Handler>(BaseActionHandler);
		ForceEdgeComboA1Handler->bCacheInput = true;
		return false;
	}
	
	if(CurrentHandleAction.ActionType == EActionType::N_Combo_A2 &&
		CurrentHandleAction.WeaponType == EWeaponType::ForceEdge &&
		CurrentHandleAction.ActionLifeCycle < EActionLifeCycle::After_1)
	{
		UManyClickManyTriggeredHandler* ManyClickManyTriggeredHandler = Cast<UManyClickManyTriggeredHandler>(BaseActionHandler);
		ManyClickManyTriggeredHandler->Trigger();
		return false;
	}

	if(CurrentHandleAction.ActionType == EActionType::S_ForceEdge_Front_Attack_After &&
	CurrentHandleAction.WeaponType == EWeaponType::ForceEdge &&
	CurrentHandleAction.ActionLifeCycle < EActionLifeCycle::After_1)
	{
		UManyClickManyTriggeredHandler* ManyClickManyTriggeredHandler = Cast<UManyClickManyTriggeredHandler>(BaseActionHandler);
		ManyClickManyTriggeredHandler->Trigger();
		return false;
	}
	
		
	if(ActionComponent->CurrentHandler->HandleAction.ActionLifeCycle >= EActionLifeCycle::After_3 && ActionComponent->CurrentHandler->Break(this))
	{
		BreakEnterHandle();
		return true;
	}

	return false;
}

bool UForceEdgeComboAHandler::WaitHandle()
{
	return Super::WaitHandle();
}
