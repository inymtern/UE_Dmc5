// Fill out your copyright notice in the Description page of Project Settings.


#include "HitLandedHandler.h"

#include "HitVectorHandler.h"
#include "Dmcv2/Dmc/Character/BaseCharacter.h"
#include "Dmcv2/Dmc/Tools/UPrintTool.h"
#include "GameFramework/CharacterMovementComponent.h"

void UHitLandedHandler::Pre_1()
{
	bNeedUp = CharacterMovementComponent->Velocity.Z < -2000;
	Super::Pre_1();
}

void UHitLandedHandler::Setup(ABaseCharacter* Character)
{
	Super::Setup(Character);
	ActionComponent->FindAction(HandleAction, EWeaponType::None, EActionType::Hit_Land);
}

void UHitLandedHandler::CommonSignal_1()
{
	if(bNeedUp)
	{
		UBaseActionHandler* BaseActionHandler = ActionComponent->FindActionHandler(EWeaponType::None, EActionType::Hit_Vector);
		UHitVectorHandler* HitVectorHandler = Cast<UHitVectorHandler>(BaseActionHandler);
		HitVectorHandler->Vector = FVector(0,0, 1400);
		HitVectorHandler->Pre_1();
	}
}

void UHitLandedHandler::End()
{
	Super::End();
	ActionComponent->FindActionHandlerExec(EWeaponType::None, EActionType::Hit_Getup);
}
