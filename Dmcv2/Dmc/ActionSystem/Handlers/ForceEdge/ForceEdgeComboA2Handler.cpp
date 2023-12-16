// Fill out your copyright notice in the Description page of Project Settings.


#include "ForceEdgeComboA2Handler.h"

void UForceEdgeComboA2Handler::Setup(ABaseCharacter* Character)
{
	Super::Setup(Character);
	ActionComponent->FindAction(HandleAction, EWeaponType::ForceEdge, EActionType::N_Combo_A2);
}

void UForceEdgeComboA2Handler::After_1()
{
	if(!bSaved || CurrentTriggerCount >= MaxTriggerCount)
	{
		if(CurrentTriggerCount < MaxTriggerCount)
		{
			Super::After_1();
			EnterNext();
		}else
		{
			Super::After_2();
			ActionComponent->FindActionHandlerExec(HandleAction.WeaponType, HandleAction.CurrentAnim.SubActionType);
		}
	}else
	{
		bSaved = false;
		ActionComponent->bToggleSignal = !ActionComponent->bToggleSignal;
	}
}





