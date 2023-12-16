// Fill out your copyright notice in the Description page of Project Settings.


#include "YamatoAirComboAHandler.h"
#include "Dmcv2/Dmc/Character/BaseCharacter.h"

#include "GameFramework/CharacterMovementComponent.h"

void UYamatoAirComboAHandler::Setup(ABaseCharacter* Character)
{
	Super::Setup(Character);
	ActionComponent->FindAction(HandleAction, EWeaponType::Yamato, EActionType::N_Air_Combo_A);
}

bool UYamatoAirComboAHandler::BeforeEnter()
{
	if(ActionComponent->CurrentHandler == this)
	{
		SelfEnterHandle();
		return true;
	}

	UBaseActionHandler* CurrentBaseActionHandler = ActionComponent->CurrentHandler;
	const FAction CurrentHandleAction = CurrentBaseActionHandler->HandleAction;

	if(CurrentHandleAction.ActionType == N_Air_Combo_A1 &&
		CurrentHandleAction.WeaponType == EWeaponType::Yamato &&
		CurrentHandleAction.ActionLifeCycle <= EActionLifeCycle::Exec &&
		CurrentHandleAction.Index == 0)
	{
		UComboHandler* ComboHandler = Cast<UComboHandler>(CurrentBaseActionHandler);
		ComboHandler->bCacheInput = true;
	}
	
	if(CurrentHandleAction.ActionLifeCycle >= EActionLifeCycle::After_1 && CurrentBaseActionHandler->Break(this))
	{
		BreakEnterHandle();
		return true;
	}

	return false;
}



void UYamatoAirComboAHandler::Pre_1()
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

void UYamatoAirComboAHandler::After_3()
{
	Super::After_3();
	ResetAir();
}

bool UYamatoAirComboAHandler::Break(UBaseActionHandler* SourceActionHandler)
{
	ResetAir();
	return Super::Break(SourceActionHandler);
}

bool UYamatoAirComboAHandler::WaitHandle()
{
	return Super::WaitHandle();
}

void UYamatoAirComboAHandler::KeepAir() const
{
	CharacterMovementComponent->Velocity = FVector::Zero();
	CharacterMovementComponent->GravityScale = SelfCharacter->DefaultAirGravity;
}

void UYamatoAirComboAHandler::ResetAir() const
{
	CharacterMovementComponent->GravityScale = SelfCharacter->DefaultGravity;
}


