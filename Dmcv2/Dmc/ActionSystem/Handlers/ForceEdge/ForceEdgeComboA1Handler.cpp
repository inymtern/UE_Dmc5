// Fill out your copyright notice in the Description page of Project Settings.


#include "ForceEdgeComboA1Handler.h"

void UForceEdgeComboA1Handler::Setup(ABaseCharacter* Character)
{
	Super::Setup(Character);
	ActionComponent->FindAction(HandleAction, EWeaponType::ForceEdge, EActionType::N_Combo_A1);
}

bool UForceEdgeComboA1Handler::BeforeEnter()
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

void UForceEdgeComboA1Handler::BreakEnterHandle()
{
	Super::BreakEnterHandle();
	bCacheInput = false;
}

void UForceEdgeComboA1Handler::After_1()
{
	Super::After_1();
	if(bCacheInput)
	{
		Super::After_2();
		ActionComponent->FindActionHandlerExec(HandleAction.WeaponType, HandleAction.CurrentAnim.SubActionType);
		bCacheInput = false;
	}
}
