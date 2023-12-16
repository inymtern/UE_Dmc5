// Fill out your copyright notice in the Description page of Project Settings.


#include "ComboHandler.h"
#include "Dmcv2/Dmc/Character/BaseCharacter.h"

void UComboHandler::Setup(ABaseCharacter* Character)
{
	Super::Setup(Character);
}

void UComboHandler::SelfEnterHandle()
{
	Super::SelfEnterHandle();
}

void UComboHandler::BreakEnterHandle()
{
	Super::BreakEnterHandle();
	bCacheInput = false;
}

bool UComboHandler::BeforeEnter()
{
	if(ActionComponent->CurrentHandler == this)
	{
		SelfEnterHandle();
		return true;
	}
		
	if(ActionComponent->CurrentHandler->HandleAction.ActionLifeCycle >= EActionLifeCycle::After_3 && ActionComponent->CurrentHandler->Break(this))
	{
		BreakEnterHandle();
		return true;
	}

	return false;
}

void UComboHandler::Pre_1()
{
	if(!BeforeEnter()) return;

	if(HandleAction.Index >= HandleAction.AnimArray.Num() - 1)
	{
		HandleAction.Index = -1;
	}
	if(HandleAction.ActionLifeCycle <= EActionLifeCycle::Exec )
	{
		bCacheInput = true;
		return;
	}

	if(HandleAction.ActionLifeCycle == EActionLifeCycle::After_2)
	{
		if(WaitHandle())
		{
			return;
		}
	}
	
	HandleAction.ActionLifeCycle = EActionLifeCycle::Pre_1;
	HandleAction.Index++;
	HandleAction.CurrentAnim = HandleAction.AnimArray[HandleAction.Index];
	ActionComponent->bToggleSignal = !ActionComponent->bToggleSignal;
}

void UComboHandler::Pre_2()
{
	Super::Pre_2();
}

void UComboHandler::Pre_3()
{
	Super::Pre_3();
}

void UComboHandler::Exec()
{
	Super::Exec();
}

void UComboHandler::After_1()
{
	Super::After_1();
	if(bCacheInput)
	{
		Pre_1();
		bCacheInput = false;
	}
}

void UComboHandler::After_2()
{
	Super::After_2();
}

void UComboHandler::After_3()
{
	Super::After_3();
}

void UComboHandler::End()
{
	Super::End();
}

void UComboHandler::CommonSignal_1()
{
	Super::CommonSignal_1();
}

void UComboHandler::CommonSignal_2()
{
	Super::CommonSignal_2();
}

void UComboHandler::CommonSignal_3()
{
	Super::CommonSignal_3();
}

bool UComboHandler::Break(UBaseActionHandler* SourceActionHandler)
{
	return Super::Break(SourceActionHandler);
}

bool UComboHandler::WaitHandle()
{
	if (ActionComponent->FindActionHandlerExec(HandleAction.WeaponType, HandleAction.CurrentAnim.SubActionType))
	{
		return true;
	}
	return false;
}
