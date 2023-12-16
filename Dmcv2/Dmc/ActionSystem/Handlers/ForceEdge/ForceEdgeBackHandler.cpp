// Fill out your copyright notice in the Description page of Project Settings.


#include "ForceEdgeBackHandler.h"

#include "Dmcv2/Dmc/Character/BaseCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"

void UForceEdgeBackHandler::Setup(ABaseCharacter* Character)
{
	Super::Setup(Character);
	ActionComponent->FindAction(HandleAction, EWeaponType::ForceEdge, EActionType::N_Back_Attack);
}

void UForceEdgeBackHandler::CommonSignal_1()
{
	CharacterMovementComponent->AddImpulse(Height, true);
}


