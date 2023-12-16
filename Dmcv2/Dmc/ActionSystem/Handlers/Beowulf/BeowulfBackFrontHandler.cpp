// Fill out your copyright notice in the Description page of Project Settings.


#include "BeowulfBackFrontHandler.h"

#include "GameFramework/CharacterMovementComponent.h"

void UBeowulfBackFrontHandler::Setup(ABaseCharacter* Character)
{
	Super::Setup(Character);
	ActionComponent->FindAction(HandleAction, EWeaponType::Beowulf, EActionType::N_Back_Front_Attack);
}

void UBeowulfBackFrontHandler::Exec()
{
	HandleAction.ActionLifeCycle = EActionLifeCycle::Exec;
}

void UBeowulfBackFrontHandler::After_1()
{
	Super::After_1();
	if(!bReleased && CurrentPressTime >= LongPressTime)
	{
		HandleAction.Index = 1;
		HandleAction.CurrentAnim = HandleAction.AnimArray[HandleAction.Index];
		ActionComponent->bToggleSignal = !ActionComponent->bToggleSignal;
	}
}

void UBeowulfBackFrontHandler::CommonSignal_1()
{
	CharacterMovementComponent->AddImpulse(FVector(0,0,1600), true);
	
}
