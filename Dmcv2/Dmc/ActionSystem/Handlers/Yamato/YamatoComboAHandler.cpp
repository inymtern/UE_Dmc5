// Fill out your copyright notice in the Description page of Project Settings.


#include "YamatoComboAHandler.h"

#include "Dmcv2/Dmc/ActionSystem/Handlers/ManyClickManyTriggeredHandler.h"

void UYamatoComboAHandler::Setup(ABaseCharacter* Character)
{
	Super::Setup(Character);
	ActionComponent->FindAction(HandleAction, EWeaponType::Yamato, EActionType::N_Combo_A);
}

bool UYamatoComboAHandler::BeforeEnter()
{
	if(ActionComponent->CurrentHandler == this)
	{
		SelfEnterHandle();
		return true;
	}
	UBaseActionHandler* BaseActionHandler = ActionComponent->CurrentHandler;
	const FAction CurrentHandleAction = ActionComponent->CurrentHandler->HandleAction;

	
	if(CurrentHandleAction.ActionType == EActionType::N_Combo_A2 &&
		CurrentHandleAction.WeaponType == EWeaponType::Yamato &&
		CurrentHandleAction.ActionLifeCycle < EActionLifeCycle::After_1)
	{
		UManyClickManyTriggeredHandler* ManyClickManyTriggeredHandler = Cast<UManyClickManyTriggeredHandler>(BaseActionHandler);
		ManyClickManyTriggeredHandler->Trigger();
		return false;
	}
		
	if(CurrentHandleAction.ActionLifeCycle >= EActionLifeCycle::After_3 && BaseActionHandler->Break(this))
	{
		BreakEnterHandle();
		return true;
	}
	return false;
}


