// Fill out your copyright notice in the Description page of Project Settings.


#include "HitVectorHandler.h"

#include "GameFramework/CharacterMovementComponent.h"

void UHitVectorHandler::Setup(ABaseCharacter* Character)
{
	Super::Setup(Character);
	ActionComponent->FindAction(HandleAction, EWeaponType::None, EActionType::Hit_Vector);
}

void UHitVectorHandler::Pre_1()
{
	if(!BeforeEnter()) return;

	CharacterMovementComponent->Velocity = FVector::Zero();
	HandleAction.ActionLifeCycle = EActionLifeCycle::Pre_1;
	HandleAction.Index = 0;
	HandleAction.CurrentAnim = HandleAction.AnimArray[HandleAction.Index];
	ActionComponent->bToggleSignal = !ActionComponent->bToggleSignal;
}

void UHitVectorHandler::CommonSignal_1()
{
	if(Vector.IsZero())
	{
		Vector = FVector(0,0,1600);
	}
	CharacterMovementComponent->AddImpulse(Vector, true);
}
