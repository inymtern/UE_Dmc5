// Fill out your copyright notice in the Description page of Project Settings.


#include "HitSilentHandler.h"

#include "Dmcv2/Dmc/Character/BaseCharacter.h"
#include "Dmcv2/Dmc/Tools/UPrintTool.h"
#include "GameFramework/CharacterMovementComponent.h"

void UHitSilentHandler::Setup(ABaseCharacter* Character)
{
	Super::Setup(Character);
	ActionComponent->FindAction(HandleAction, EWeaponType::None, EActionType::Hit_Silent);
}

void UHitSilentHandler::Pre_1()
{
	if(!BeforeEnter()) return;
	HandleAction.ActionLifeCycle = EActionLifeCycle::Pre_1;
	if(CharacterMovementComponent->IsFalling())
	{
		CharacterMovementComponent->Velocity = FVector::Zero();
		CharacterMovementComponent->GravityScale = 0;
		HandleAction.Index = 1;
	}else
	{
		HandleAction.Index = 0;
	}
	HandleAction.CurrentAnim = HandleAction.AnimArray[HandleAction.Index];
	ActionComponent->bToggleSignal = !ActionComponent->bToggleSignal;
}

void UHitSilentHandler::CommonSignal_2()
{
	EnterSilent();
}

bool UHitSilentHandler::Break(UBaseActionHandler* SourceActionHandler)
{
	
	if(bFinish || SourceActionHandler->HandleAction.ActionType == Hit_Vector)
	{
		CharacterMovementComponent->GravityScale = SelfCharacter->DefaultGravity;
		BreakSilent();
		return true;
	}
	if(SourceActionHandler->HandleAction.ActionType == Hit_Normal)
	{
		BreakSilent();
		HandleAction.ActionLifeCycle = EActionLifeCycle::After_1;
		Pre_1();
	}
	return false;
}

void UHitSilentHandler::EnterSilent()
{
	bFinish = false;
	HandleAction.CurrentAnim.PlayRate = PlayRate;
	SelfCharacter->BasicPlayRate = PlayRate;
	GetWorld()->GetTimerManager().SetTimer(SilentTimerHandle, this, &UHitSilentHandler::BreakSilent, Duration, false);
}

void UHitSilentHandler::BreakSilent()
{
	GetWorld()->GetTimerManager().ClearTimer(SilentTimerHandle);
	bFinish = true;
	CharacterMovementComponent->GravityScale = SelfCharacter->DefaultGravity;
	SelfCharacter->BasicPlayRate = 1;
	HandleAction.CurrentAnim.PlayRate = 1;
}
