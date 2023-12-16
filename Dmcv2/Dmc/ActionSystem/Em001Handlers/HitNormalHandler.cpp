// Fill out your copyright notice in the Description page of Project Settings.


#include "HitNormalHandler.h"

#include "Dmcv2/Dmc/Anim/Notify/Offset.h"
#include "Dmcv2/Dmc/Character/BaseCharacter.h"
#include "Dmcv2/Dmc/Tools/MathTool.h"
#include "Dmcv2/Dmc/Tools/UPrintTool.h"
#include "GameFramework/CharacterMovementComponent.h"

void UHitNormalHandler::Setup(ABaseCharacter* Character)
{
	Super::Setup(Character);
	ActionComponent->FindAction(HandleAction, EWeaponType::None, EActionType::Hit_Normal);
}

void UHitNormalHandler::Pre_1()
{
	if(!BeforeEnter()) return;
	HandleAction.ActionLifeCycle = EActionLifeCycle::Pre_1;
	if(CharacterMovementComponent->IsFalling())
	{
		
		CharacterMovementComponent->Velocity = FVector::Zero();
		CharacterMovementComponent->GravityScale = SelfCharacter->DefaultAirGravity;
		SelfCharacter->LaunchCharacter(FVector(0,0,80), true,true);
		HandleAction.Index = 2;
	}else
	{
		if(SourceCharacter)
		{
			const ECustomDir Direction = UMathTool::CalcRefDirection(SelfCharacter->GetActorForwardVector(), SelfCharacter->GetActorLocation(), SourceCharacter->GetActorLocation());
			HandleAction.Index = Direction == ECustomDir::D_Front ? 0 : 1;
		}else
		{
			HandleAction.Index = 0;
		}
	}
	HandleAction.CurrentAnim = HandleAction.AnimArray[HandleAction.Index];
	ActionComponent->bToggleSignal = !ActionComponent->bToggleSignal;
}

void UHitNormalHandler::CommonSignal_1()
{
	if (AirTime == 0)
	{
		CharacterMovementComponent->GravityScale = SelfCharacter->DefaultGravity;
	}else
	{
		auto Lambda = [this]()
		{
			CharacterMovementComponent->GravityScale = SelfCharacter->DefaultGravity;
		};
		GetWorld()->GetTimerManager().SetTimer(AirTimerHandle, Lambda, AirTime, false);
	}
	
}

bool UHitNormalHandler::Break(UBaseActionHandler* SourceActionHandler)
{
	CharacterMovementComponent->GravityScale = SelfCharacter->DefaultGravity;
	return Super::Break(SourceActionHandler);
}
