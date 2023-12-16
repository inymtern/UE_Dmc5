// Fill out your copyright notice in the Description page of Project Settings.


#include "BeowulfBackHandler.h"

#include "Dmcv2/Dmc/Tools/UPrintTool.h"
#include "GameFramework/CharacterMovementComponent.h"

void UBeowulfBackHandler::Setup(ABaseCharacter* Character)
{
	Super::Setup(Character);
	ActionComponent->FindAction(HandleAction, EWeaponType::Beowulf, EActionType::N_Back_Attack);
}

void UBeowulfBackHandler::CommonSignal_1()
{
	CharacterMovementComponent->AddImpulse(FVector(0,0, 1600), true);
}

void UBeowulfBackHandler::FinishReleased()
{
	if(bCrossPre2)
	{
		bCrossPre2 = false;
		HandleAction.Index = 3;
		HandleAction.CurrentAnim = HandleAction.AnimArray[HandleAction.Index];
		ActionComponent->bToggleSignal = !ActionComponent->bToggleSignal;
	}
}

