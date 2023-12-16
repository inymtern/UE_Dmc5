// Fill out your copyright notice in the Description page of Project Settings.


#include "FlashHandler.h"

#include "Dmcv2/Dmc/Character/BaseCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"

bool UFlashHandler::BeforeEnter()
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
		if(HandleAction.ActionLifeCycle != EActionLifeCycle::Exec && ActionComponent->CurrentHandler->Break(this))
		{
			BreakEnterHandle();
			return true;
		}
	}
	return false;
}

void UFlashHandler::Setup(ABaseCharacter* Character)
{
	Super::Setup(Character);
	ActionComponent->FindAction(HandleAction, EWeaponType::None, EActionType::Flash);
}

void UFlashHandler::Exec()
{
	HandleAction.ActionLifeCycle = EActionLifeCycle::Exec;
	bFallingAndMiss = false;
	if(SelfCharacter->FocusCharacter)
	{
		End = SelfCharacter->FocusCharacter->GetSafeClosePlace(SelfCharacter->GetActorLocation());
	
		bEndIsAir = SelfCharacter->FocusCharacter->GetCharacterMovement()->IsFalling();

		CharacterMovementComponent->Velocity = FVector::Zero();
	}else
	{
		if(CharacterMovementComponent->IsFalling())
		{
			bFallingAndMiss = true;
			CharacterMovementComponent->AddImpulse(FVector(0,0,-3000), true);
			return;
		}
		
		End = SelfCharacter->GetActorLocation();
	}
	GetWorld()->GetTimerManager().SetTimer(OffsetTimerHandle, this, &UFlashHandler::Flash, GetWorld()->GetDeltaSeconds(), true);
}

void UFlashHandler::After_1()
{
	HandleAction.ActionLifeCycle = EActionLifeCycle::After_1;
	if(bEndIsAir)
	{
		CharacterMovementComponent->GravityScale = SelfCharacter->DefaultAirGravity;
	}
}

void UFlashHandler::After_3()
{
	HandleAction.ActionLifeCycle = EActionLifeCycle::After_3;
	if(bEndIsAir)
	{
		CharacterMovementComponent->GravityScale = SelfCharacter->DefaultGravity;
	}
}

void UFlashHandler::Landed()
{
	HandleAction.Index = 1;
	HandleAction.CurrentAnim = HandleAction.AnimArray[HandleAction.Index];
	ActionComponent->bToggleSignal = !ActionComponent->bToggleSignal;
}

bool UFlashHandler::Break(UBaseActionHandler* SourceActionHandler)
{
	CharacterMovementComponent->GravityScale = SelfCharacter->DefaultGravity;
	return Super::Break(SourceActionHandler);
}

void UFlashHandler::Flash()
{
	Start = SelfCharacter->GetActorLocation();

	const FVector VInterpTo = FMath::VInterpTo(Start, End, GetWorld()->GetDeltaSeconds(), Speed);
	SelfCharacter->SetActorLocation(VInterpTo);

	const double Distance = FVector::Distance(Start, End);
	if(Distance < MinDistance)
	{
		SelfCharacter->RotateTo(SelfCharacter->FocusCharacter);
		GetWorld()->GetTimerManager().ClearTimer(OffsetTimerHandle);
		if(bEndIsAir)
		{
			HandleAction.Index = 2;
			HandleAction.CurrentAnim = HandleAction.AnimArray[HandleAction.Index];
			ActionComponent->bToggleSignal = !ActionComponent->bToggleSignal;
		}else
		{
			HandleAction.Index = 1;
			HandleAction.CurrentAnim = HandleAction.AnimArray[HandleAction.Index];
			ActionComponent->bToggleSignal = !ActionComponent->bToggleSignal;
		}
	}
}


