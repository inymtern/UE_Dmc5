// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseHitHandler.h"

bool UBaseHitHandler::BeforeEnter()
{
	if(ActionComponent->CurrentHandler == this)
	{
		if(HandleAction.ActionLifeCycle >= EActionLifeCycle::After_1)
		{
			SelfEnterHandle();
			return true;
		}
	}else
	{
		if(ActionComponent->CurrentHandler->Break(this))
		{
			BreakEnterHandle();
			return true;
		}
	}
	return false;
}
