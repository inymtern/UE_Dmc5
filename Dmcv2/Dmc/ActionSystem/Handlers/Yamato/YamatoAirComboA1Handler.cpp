﻿// Fill out your copyright notice in the Description page of Project Settings.


#include "YamatoAirComboA1Handler.h"
#include "Dmcv2/Dmc/Character/BaseCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"

void UYamatoAirComboA1Handler::Setup(ABaseCharacter* Character)
{
	Super::Setup(Character);
	ActionComponent->FindAction(HandleAction, EWeaponType::Yamato, EActionType::N_Air_Combo_A1);
}

bool UYamatoAirComboA1Handler::BeforeEnter()
{
	if(ActionComponent->CurrentHandler == this)
	{
		return true;
	}
		
	if(ActionComponent->CurrentHandler->HandleAction.ActionLifeCycle == EActionLifeCycle::After_2 && ActionComponent->CurrentHandler->Break(this))
	{
		BreakEnterHandle();
		return true;
	}

	return false;
}

void UYamatoAirComboA1Handler::Pre_1()
{
	if(!BeforeEnter()) return;

	if(HandleAction.Index >= HandleAction.AnimArray.Num() - 1)
	{
		HandleAction.Index = -1;
	}
	if(HandleAction.ActionLifeCycle <= EActionLifeCycle::Exec )
	{
		bCacheInput = true;
		return;
	}

	if(HandleAction.ActionLifeCycle == EActionLifeCycle::After_2)
	{
		if(WaitHandle())
		{
			return;
		}
	}
	
	HandleAction.ActionLifeCycle = EActionLifeCycle::Pre_1;
	HandleAction.Index++;
	HandleAction.CurrentAnim = HandleAction.AnimArray[HandleAction.Index];
	ActionComponent->bToggleSignal = !ActionComponent->bToggleSignal;

	KeepAir();
}

void UYamatoAirComboA1Handler::After_1()
{
	Super::After_1();
}

void UYamatoAirComboA1Handler::After_3()
{
	Super::After_3();
	ResetAir();
}

bool UYamatoAirComboA1Handler::Break(UBaseActionHandler* SourceActionHandler)
{
	ResetAir();
	return Super::Break(SourceActionHandler);
}

void UYamatoAirComboA1Handler::KeepAir() const
{
	CharacterMovementComponent->Velocity = FVector::Zero();
	CharacterMovementComponent->GravityScale = SelfCharacter->DefaultAirGravity;
}

void UYamatoAirComboA1Handler::ResetAir() const
{
	CharacterMovementComponent->GravityScale = SelfCharacter->DefaultGravity;
}
