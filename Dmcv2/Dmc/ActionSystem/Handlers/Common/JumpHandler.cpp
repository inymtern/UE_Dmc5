// Fill out your copyright notice in the Description page of Project Settings.


#include "JumpHandler.h"

#include "Dmcv2/Dmc/Character/VergilCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"

void UJumpHandler::Setup(ABaseCharacter* Character)
{
	Super::Setup(Character);
	ActionComponent->FindAction(HandleAction, EWeaponType::None, EActionType::Jump);
}

bool UJumpHandler::BeforeEnter()
{
	if(ActionComponent->CurrentHandler == this)
	{
		if(HandleAction.ActionLifeCycle >= EActionLifeCycle::After_3)
		{
			SelfEnterHandle();
			return true;
		}
	}else
	{
		if(ActionComponent->CurrentHandler->HandleAction.ActionLifeCycle >= EActionLifeCycle::After_1 && ActionComponent->CurrentHandler->Break(this))
		{
			bSoon = ActionComponent->CurrentHandler->HandleAction.ActionLifeCycle <= EActionLifeCycle::After_3;
			BreakEnterHandle();
			return true;
		}
	}
	return false;
}

void UJumpHandler::Pre_1()
{
	if(!BeforeEnter()) return;
	

	
	const AVergilCharacter* VergilCharacter = Cast<AVergilCharacter>(SelfCharacter);
	
	if (VergilCharacter->LastInputDirection == EInputDirection::Front || VergilCharacter->LastInputDirection == EInputDirection::BackFront)
	{
		HandleAction.Index = 1;
	}else if(VergilCharacter->LastInputDirection == EInputDirection::Nil)
	{
		HandleAction.Index = 0;
	}else if(VergilCharacter->LastInputDirection == EInputDirection::Back )
	{
		HandleAction.Index = 2;
	}else if(VergilCharacter->LastInputDirection == EInputDirection::Left )
	{
		HandleAction.Index = 4;
	}else if(VergilCharacter->LastInputDirection == EInputDirection::Right )
	{
		HandleAction.Index = 5;
	}
	if(bSoon && HandleAction.Index >= 4 && SelfCharacter->FocusCharacter)
	{
		ActionComponent->FindActionHandlerExec(EWeaponType::None, EActionType::Attack_Flash);
	}else
	{
		HandleAction.ActionLifeCycle = EActionLifeCycle::Pre_1;
		HandleAction.CurrentAnim = HandleAction.AnimArray[HandleAction.Index];
		ActionComponent->bToggleSignal = !ActionComponent->bToggleSignal;
	}
}

void UJumpHandler::Exec()
{
	Super::Exec();
	CharacterMovementComponent->Velocity = FVector::Zero();
	if(HandleAction.Index < 4)
	{
		CharacterMovementComponent->AddImpulse(Velocity, true);
	}
	
}

void UJumpHandler::After_1()
{
	Super::After_1();
	CharacterMovementComponent->AddImpulse(DeVelocity, true);
}





void UJumpHandler::Landed()
{
	HandleAction.Index = 3;
	HandleAction.CurrentAnim = HandleAction.AnimArray[HandleAction.Index];
	ActionComponent->bToggleSignal = !ActionComponent->bToggleSignal;
}
