// Fill out your copyright notice in the Description page of Project Settings.


#include "YamatoAirBackHandler.h"

#include "Dmcv2/Dmc/Character/BaseCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Math/UnitConversion.h"

void UYamatoAirBackHandler::Setup(ABaseCharacter* Character)
{
	Super::Setup(Character);
	ActionComponent->FindAction(HandleAction, EWeaponType::Yamato, EActionType::N_Air_Back_Attack);
}

void UYamatoAirBackHandler::Pre_1()
{
	if(!BeforeEnter()) return;
	HandleAction.ActionLifeCycle = EActionLifeCycle::Pre_1;
	HandleAction.Index = 0;
	HandleAction.CurrentAnim = HandleAction.AnimArray[HandleAction.Index];
	ActionComponent->bToggleSignal = !ActionComponent->bToggleSignal;

	CharacterMovementComponent->Velocity = FVector::Zero();
	CharacterMovementComponent->GravityScale = 0;
}

void UYamatoAirBackHandler::Exec()
{
	Super::Exec();
	CharacterMovementComponent->GravityScale = SelfCharacter->DefaultGravity;
	CharacterMovementComponent->AddImpulse(Speed, true);
	
}

void UYamatoAirBackHandler::After_1()
{
	HandleAction.ActionLifeCycle = EActionLifeCycle::After_1;
}

void UYamatoAirBackHandler::Landed()
{
	HandleAction.Index = 2;
	HandleAction.CurrentAnim = HandleAction.AnimArray[HandleAction.Index];
	ActionComponent->bToggleSignal = !ActionComponent->bToggleSignal;
}

bool UYamatoAirBackHandler::Break(UBaseActionHandler* SourceActionHandler)
{
	CharacterMovementComponent->GravityScale = SelfCharacter->DefaultGravity;
	return Super::Break(SourceActionHandler);
}
