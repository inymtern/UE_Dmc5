// Fill out your copyright notice in the Description page of Project Settings.


#include "DeFlashHandler.h"

#include "Dmcv2/Dmc/Character/BaseCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"

void UDeFlashHandler::Setup(ABaseCharacter* Character)
{
	Super::Setup(Character);
	ActionComponent->FindAction(HandleAction, EWeaponType::None, EActionType::De_Flash);
}

bool UDeFlashHandler::BeforeEnter()
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

void UDeFlashHandler::Exec()
{
	HandleAction.ActionLifeCycle = EActionLifeCycle::Exec;

	Start = SelfCharacter->GetActorLocation();
	if(CharacterMovementComponent->IsFalling())
	{
		FRotator Rotation = SelfCharacter->GetActorForwardVector().Rotation();
		Rotation.Pitch -= 100;
		CharacterMovementComponent->AddImpulse(Rotation.Vector() * DownSpeed, true);
	}else
	{
		if(SelfCharacter->FocusCharacter)
		{
			End = CalcBackLocation();
		}else
		{
			End = Start;
		}
		GetWorld()->GetTimerManager().SetTimer(FlashTimerHandle, this, &UDeFlashHandler::DeFlash, GetWorld()->GetDeltaSeconds(), true);
	}

}

void UDeFlashHandler::After_1()
{
	HandleAction.ActionLifeCycle = EActionLifeCycle::After_1;
}

void UDeFlashHandler::Landed()
{
	HandleAction.Index = 1;
	HandleAction.CurrentAnim = HandleAction.AnimArray[HandleAction.Index];
	ActionComponent->bToggleSignal = !ActionComponent->bToggleSignal;
}

void UDeFlashHandler::DeFlash()
{
	Start = FMath::VInterpTo(Start, End, GetWorld()->GetDeltaSeconds(), Speed);
	
	SelfCharacter->SetActorLocation(Start);

	if(FVector::Distance(Start, End) < MinDistance)
	{
		SelfCharacter->RotateTo(SelfCharacter->FocusCharacter);
		GetWorld()->GetTimerManager().ClearTimer(FlashTimerHandle);
		Landed();
	}
}

FVector UDeFlashHandler::CalcBackLocation() const
{
	return SelfCharacter->GetActorLocation() + SelfCharacter->GetActorForwardVector() * BackDistance * -1;
}
