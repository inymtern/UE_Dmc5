// Fill out your copyright notice in the Description page of Project Settings.


#include "BeowulfFrontHandler.h"

void UBeowulfFrontHandler::Setup(ABaseCharacter* Character)
{
	Super::Setup(Character);
	ActionComponent->FindAction(HandleAction, EWeaponType::Beowulf, EActionType::N_Front_Attack);
}

void UBeowulfFrontHandler::Exec()
{
	Super::Exec();
}

void UBeowulfFrontHandler::CommonSignal_1()
{
	HandleAction.Index++;
	HandleAction.CurrentAnim = HandleAction.AnimArray[HandleAction.Index];
	ActionComponent->bToggleSignal = !ActionComponent->bToggleSignal;
}

void UBeowulfFrontHandler::After_1()
{
	Super::After_1();
}
