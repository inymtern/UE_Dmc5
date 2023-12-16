// Fill out your copyright notice in the Description page of Project Settings.


#include "ForceEdgeComboA3Handler.h"

#include "GameFramework/CharacterMovementComponent.h"

void UForceEdgeComboA3Handler::Setup(ABaseCharacter* Character)
{
	Super::Setup(Character);
	ActionComponent->FindAction(HandleAction, EWeaponType::ForceEdge, EActionType::N_Combo_A3);
}

void UForceEdgeComboA3Handler::CommonSignal_1()
{
	CharacterMovementComponent->AddImpulse(FVector(0,0,350), true);
}