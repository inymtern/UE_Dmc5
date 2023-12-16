// Fill out your copyright notice in the Description page of Project Settings.


#include "ForceEdgeFrontAttackAfterHandler.h"

void UForceEdgeFrontAttackAfterHandler::Setup(ABaseCharacter* Character)
{
	Super::Setup(Character);
	ActionComponent->FindAction(HandleAction, EWeaponType::ForceEdge, EActionType::S_ForceEdge_Front_Attack_After);
}

bool UForceEdgeFrontAttackAfterHandler::BeforeEnter()
{
	if(ActionComponent->CurrentHandler == this)
	{
		return false;
	}
	if(ActionComponent->CurrentHandler->HandleAction.ActionType == EActionType::N_Front_Attack &&
	ActionComponent->CurrentHandler->HandleAction.WeaponType == EWeaponType::ForceEdge && 
		ActionComponent->CurrentHandler->Break(this))
	{
		BreakEnterHandle();
		return true;
	}
	return false;
}
