// Fill out your copyright notice in the Description page of Project Settings.


#include "YamatoComboA1Handler.h"

void UYamatoComboA1Handler::Setup(ABaseCharacter* Character)
{
	Super::Setup(Character);
	ActionComponent->FindAction(HandleAction, EWeaponType::Yamato, EActionType::N_Combo_A1);
}

bool UYamatoComboA1Handler::BeforeEnter()
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
