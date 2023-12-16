// Fill out your copyright notice in the Description page of Project Settings.


#include "LandedHandler.h"

void ULandedHandler::Setup(ABaseCharacter* Character)
{
	Super::Setup(Character);
	ActionComponent->FindAction(HandleAction, EWeaponType::None, EActionType::Landed);
}

bool ULandedHandler::BeforeEnter()
{
	if(ActionComponent->CurrentHandler == this)
	{
		return false;
	}
	{
		if(HandleAction.ActionLifeCycle >= EActionLifeCycle::After_1 && ActionComponent->CurrentHandler->Break(this))
		{
			BreakEnterHandle();
			return true;
		}
	}
	return false;
}

void ULandedHandler::Pre_1()
{
	Super::Pre_1();
}
