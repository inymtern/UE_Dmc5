// Fill out your copyright notice in the Description page of Project Settings.


#include "ForceEdgeAirFrontHandler.h"

#include "Dmcv2/Dmc/Character/BaseCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"

void UForceEdgeAirFrontHandler::Setup(ABaseCharacter* Character)
{
	Super::Setup(Character);
	ActionComponent->FindAction(HandleAction, EWeaponType::ForceEdge, EActionType::N_Air_Front_Attack);
}

void UForceEdgeAirFrontHandler::CommonSignal_1()
{
	CharacterMovementComponent->Velocity = FVector::Zero();
	CharacterMovementComponent->GravityScale = 0;
}

void UForceEdgeAirFrontHandler::CommonSignal_2()
{
	CharacterMovementComponent->GravityScale = SelfCharacter->DefaultGravity;
}

bool UForceEdgeAirFrontHandler::Break(UBaseActionHandler* SourceActionHandler)
{
	CharacterMovementComponent->GravityScale = SelfCharacter->DefaultGravity;
	return Super::Break(SourceActionHandler);
}


