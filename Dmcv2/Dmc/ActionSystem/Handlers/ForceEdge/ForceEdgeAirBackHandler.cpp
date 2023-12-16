// Fill out your copyright notice in the Description page of Project Settings.


#include "ForceEdgeAirBackHandler.h"

#include "GameFramework/CharacterMovementComponent.h"

void UForceEdgeAirBackHandler::Setup(ABaseCharacter* Character)
{
	Super::Setup(Character);
	ActionComponent->FindAction(HandleAction, EWeaponType::ForceEdge, EActionType::N_Air_Back_Attack);
}

void UForceEdgeAirBackHandler::Exec()
{
	Super::Exec();
	CharacterMovementComponent->AddImpulse(Speed, true);
}

void UForceEdgeAirBackHandler::After_1()
{
	HandleAction.ActionLifeCycle = EActionLifeCycle::After_1;
}

void UForceEdgeAirBackHandler::Landed()
{
	HandleAction.Index = 2;
	HandleAction.CurrentAnim = HandleAction.AnimArray[HandleAction.Index];
	ActionComponent->bToggleSignal = !ActionComponent->bToggleSignal;
}
