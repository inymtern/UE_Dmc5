// Fill out your copyright notice in the Description page of Project Settings.


#include "BeowulfAirComboHandler.h"

#include "Dmcv2/Dmc/Character/BaseCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"

void UBeowulfAirComboHandler::Setup(ABaseCharacter* Character)
{
	Super::Setup(Character);
	ActionComponent->FindAction(HandleAction, EWeaponType::Beowulf, EActionType::N_Air_Combo_A);
}

void UBeowulfAirComboHandler::Pre_1()
{
	if(!BeforeEnter()) return;
	HandleAction.ActionLifeCycle = EActionLifeCycle::Pre_1;
	HandleAction.Index = 0;
	HandleAction.CurrentAnim = HandleAction.AnimArray[HandleAction.Index];
	ActionComponent->bToggleSignal = !ActionComponent->bToggleSignal;
	CharacterMovementComponent->Velocity = FVector::Zero();
	CharacterMovementComponent->GravityScale = 0;
}

void UBeowulfAirComboHandler::CommonSignal_1()
{
	
}

void UBeowulfAirComboHandler::Exec()
{
	CharacterMovementComponent->GravityScale = SelfCharacter->DefaultGravity;
	HandleAction.ActionLifeCycle = EActionLifeCycle::Exec;
	HandleAction.Index = 1;
	HandleAction.CurrentAnim = HandleAction.AnimArray[HandleAction.Index];
	ActionComponent->bToggleSignal = !ActionComponent->bToggleSignal;
	CharacterMovementComponent->AddImpulse(CalcStarFallDirection(), true);
}

bool UBeowulfAirComboHandler::Break(UBaseActionHandler* SourceActionHandler)
{
	CharacterMovementComponent->GravityScale = SelfCharacter->DefaultGravity;
	return Super::Break(SourceActionHandler);
}

FVector UBeowulfAirComboHandler::CalcStarFallDirection() const
{
	FRotator ActorRotation = SelfCharacter->GetActorRotation();
	ActorRotation.Pitch -= 20;
	const FVector Vector = ActorRotation.Vector().GetSafeNormal();
	return Vector * 5000;
}

void UBeowulfAirComboHandler::Landed()
{
	CharacterMovementComponent->Velocity = FVector::Zero();
	HandleAction.Index = 2;
	HandleAction.CurrentAnim = HandleAction.AnimArray[HandleAction.Index];
	ActionComponent->bToggleSignal = !ActionComponent->bToggleSignal;
}
