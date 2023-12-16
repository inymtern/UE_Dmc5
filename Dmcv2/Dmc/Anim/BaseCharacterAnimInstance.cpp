// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseCharacterAnimInstance.h"

#include "Dmcv2/Dmc/ActionSystem/Handlers/BaseActionHandler.h"
#include "Dmcv2/Dmc/Character/BaseCharacter.h"
#include "Dmcv2/Dmc/Tools/UPrintTool.h"
#include "GameFramework/CharacterMovementComponent.h"

void UBaseCharacterAnimInstance::NativeInitializeAnimation()
{
	AActor* OwningActor = GetOwningActor();
	if(!BaseCharacter)
	{
		BaseCharacter = Cast<ABaseCharacter>(OwningActor);
	}
}

void UBaseCharacterAnimInstance::NativeThreadSafeUpdateAnimation(float DeltaSeconds)
{
	if(!BaseCharacter) return;
	const UBaseActionComponent* BaseActionComponent = BaseCharacter->BaseActionComponent;
	if(!BaseActionComponent) return;
	bIsFalling = BaseCharacter->GetCharacterMovement()->IsFalling();
	MoveAxisValue = BaseCharacter->MoveAxisValue;
	FocusMoveAxisValue = BaseCharacter->FocusMoveAxisValue;
	CurrentMoveDirection = BaseCharacter->CurrentMoveDirection;
	bFocusMode = BaseCharacter->bFocusMode;
	BasicPlayRate = BaseCharacter->BasicPlayRate;
	const UBaseActionHandler* BaseActionHandler = BaseActionComponent->CurrentHandler;
	if(!BaseActionHandler) return;
	CurrentAnim = BaseActionHandler->HandleAction.CurrentAnim;
	bToggleSignal = BaseActionComponent->bToggleSignal;
	
	CurrentActionLifeCycle = BaseActionHandler->HandleAction.ActionLifeCycle;
	
}

bool UBaseCharacterAnimInstance::HandleNotify(const FAnimNotifyEvent& AnimNotifyEvent)
{
	if(!BaseCharacter) return false;
	const UBaseActionComponent* ActionComponent = BaseCharacter->BaseActionComponent;
	if(!ActionComponent) return false;

	if(AnimNotifyEvent.NotifyName.IsEqual(FName(TEXT("Pre_2"))))
	{
		ActionComponent->CurrentHandler->Pre_2();
	}else if(AnimNotifyEvent.NotifyName.IsEqual(FName(TEXT("Pre_3"))))
	{
		ActionComponent->CurrentHandler->Pre_3();
	}else if(AnimNotifyEvent.NotifyName.IsEqual(FName(TEXT("Exec"))))
	{
		ActionComponent->CurrentHandler->Exec();
	}else if(AnimNotifyEvent.NotifyName.IsEqual(FName(TEXT("After_1"))))
	{
		ActionComponent->CurrentHandler->After_1();
	}else if(AnimNotifyEvent.NotifyName.IsEqual(FName(TEXT("After_2"))))
	{
		ActionComponent->CurrentHandler->After_2();
	}else if(AnimNotifyEvent.NotifyName.IsEqual(FName(TEXT("After_3"))))
	{
		ActionComponent->CurrentHandler->After_3();
	}else if(AnimNotifyEvent.NotifyName.IsEqual(FName(TEXT("End"))))
	{
		ActionComponent->CurrentHandler->End();
	}else if(AnimNotifyEvent.NotifyName.IsEqual(FName(TEXT("CommonSignal_1"))))
	{
		ActionComponent->CurrentHandler->CommonSignal_1();
	}else if(AnimNotifyEvent.NotifyName.IsEqual(FName(TEXT("CommonSignal_2"))))
	{
		ActionComponent->CurrentHandler->CommonSignal_2();
	}else if(AnimNotifyEvent.NotifyName.IsEqual(FName(TEXT("CommonSignal_3"))))
	{
		ActionComponent->CurrentHandler->CommonSignal_3();
	}
	
	
	return Super::HandleNotify(AnimNotifyEvent);
}
