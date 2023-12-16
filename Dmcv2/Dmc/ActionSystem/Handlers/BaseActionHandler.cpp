// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseActionHandler.h"

#include "Dmcv2/Dmc/Character/BaseCharacter.h"
#include "Dmcv2/Dmc/Tools/UPrintTool.h"

UBaseActionHandler::UBaseActionHandler()
{
}

void UBaseActionHandler::Setup(ABaseCharacter* Character)
{
	if(Character)
	{
		SelfCharacter = Character;
		ActionComponent = SelfCharacter->BaseActionComponent;
		CharacterMovementComponent = SelfCharacter->GetCharacterMovement();
	}
}

void UBaseActionHandler::SelfEnterHandle()
{
}

void UBaseActionHandler::BreakEnterHandle()
{
	ActionComponent->CurrentHandler = this;
	HandleAction.ActionLifeCycle = EActionLifeCycle::End;
	HandleAction.Index = -1;
}

bool UBaseActionHandler::BeforeEnter()
{
	if(ActionComponent->CurrentHandler == this)
	{
		if(HandleAction.ActionLifeCycle >= EActionLifeCycle::After_3)
		{
			SelfEnterHandle();
			return true;
		}
	}else
	{
		if(ActionComponent->CurrentHandler->HandleAction.ActionLifeCycle >= EActionLifeCycle::After_1 && ActionComponent->CurrentHandler->Break(this))
		{
			BreakEnterHandle();
			return true;
		}
	}
	

	return false;
}

void UBaseActionHandler::Pre_1()
{
	if(!BeforeEnter()) return;
	HandleAction.ActionLifeCycle = EActionLifeCycle::Pre_1;
	HandleAction.Index = 0;
	HandleAction.CurrentAnim = HandleAction.AnimArray[HandleAction.Index];
	ActionComponent->bToggleSignal = !ActionComponent->bToggleSignal;
}

void UBaseActionHandler::Pre_2()
{
	// pass
}

void UBaseActionHandler::Pre_3()
{
	// pass
}

void UBaseActionHandler::Exec()
{
	HandleAction.ActionLifeCycle = EActionLifeCycle::Exec;
}

void UBaseActionHandler::After_1()
{
	HandleAction.ActionLifeCycle = EActionLifeCycle::After_1;
}

void UBaseActionHandler::After_2()
{
	HandleAction.ActionLifeCycle = EActionLifeCycle::After_2;
}

void UBaseActionHandler::After_3()
{
	HandleAction.ActionLifeCycle = EActionLifeCycle::After_3;
	ResetCombo();
}

void UBaseActionHandler::ResetCombo()
{
	HandleAction.Index = -1;
}

void UBaseActionHandler::End()
{
	HandleAction.ActionLifeCycle = EActionLifeCycle::End;
	ResetCombo();
}

void UBaseActionHandler::CommonSignal_1()
{
	// pass
}

void UBaseActionHandler::CommonSignal_2()
{
	// pass
}

void UBaseActionHandler::CommonSignal_3()
{
	// pass
}

bool UBaseActionHandler::Break(UBaseActionHandler* SourceActionHandler)
{
	return true;
}
