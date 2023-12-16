// Fill out your copyright notice in the Description page of Project Settings.


#include "FlashWhenAttackHandler.h"

#include "Dmcv2/Dmc/Character/BaseCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"

bool UFlashWhenAttackHandler::BeforeEnter()
{
	if(ActionComponent->CurrentHandler == this)
	{
		return false;
	}
	if(ActionComponent->CurrentHandler->HandleAction.ActionLifeCycle >= EActionLifeCycle::After_1 && ActionComponent->CurrentHandler->Break(this))
	{
		BreakEnterHandle();
		return true;
	}	
	return false;
}

void UFlashWhenAttackHandler::Setup(ABaseCharacter* Character)
{
	Super::Setup(Character);
	ActionComponent->FindAction(HandleAction, EWeaponType::None, EActionType::Attack_Flash);
}

void UFlashWhenAttackHandler::Exec()
{
	HandleAction.ActionLifeCycle = EActionLifeCycle::Exec;

	CharacterMovementComponent->Velocity = FVector::Zero();
	SelfCharacter->SetActorHiddenInGame(true);

	Start = SelfCharacter->GetActorLocation();
	End = CalcTargetBackLocation();
	// SelfCharacter->SetActorLocation();
	SelfCharacter->SetActorEnableCollision(false);
	// FRotator ActorRotation = SelfCharacter->GetActorRotation();
	// ActorRotation.Yaw += 180;
	// SelfCharacter->SetActorRotation(ActorRotation);
	GetWorld()->GetTimerManager().SetTimer(EndTimeHandle, this, &UFlashWhenAttackHandler::CallEndAnim, GetWorld()->GetDeltaSeconds(), true);
}

void UFlashWhenAttackHandler::After_1()
{
	HandleAction.ActionLifeCycle = EActionLifeCycle::After_1;
}

void UFlashWhenAttackHandler::CallEndAnim()
{
	AddTime += GetWorld()->GetDeltaSeconds();
	FVector Vector = FMath::Lerp(Start, End, AddTime / Duration);
	SelfCharacter->SetActorLocation(Vector);
	if(AddTime >= Duration)
	{
		
		SelfCharacter->SetActorEnableCollision(true);
		GetWorld()->GetTimerManager().ClearTimer(EndTimeHandle);
		SelfCharacter->SetActorHiddenInGame(false);
		AddTime = 0;
		HandleAction.Index = 1;
		HandleAction.CurrentAnim = HandleAction.AnimArray[1];
		ActionComponent->bToggleSignal = !ActionComponent->bToggleSignal;
	}
	// 
}

FVector UFlashWhenAttackHandler::CalcTargetBackLocation()
{
	if(SelfCharacter->FocusCharacter)
	{
		
		FVector TargetLocation = SelfCharacter->FocusCharacter->GetActorLocation();
		const FVector Location = SelfCharacter->GetActorLocation();
		TargetLocation.Z = Location.Z;
		const float Distance = FVector::Distance(TargetLocation, Location) + 200;
		return SelfCharacter->GetActorForwardVector() * Distance + Location;
	}
	return SelfCharacter->GetActorLocation();
}
