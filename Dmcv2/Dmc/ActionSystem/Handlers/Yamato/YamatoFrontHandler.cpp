// Fill out your copyright notice in the Description page of Project Settings.


#include "YamatoFrontHandler.h"

#include "Dmcv2/Dmc/Character/BaseCharacter.h"
#include "Dmcv2/Dmc/Character/VergilCharacter.h"
#include "Dmcv2/Dmc/Tools/UPrintTool.h"
#include "GameFramework/CharacterMovementComponent.h"

void UYamatoFrontHandler::Setup(ABaseCharacter* Character)
{
	Super::Setup(Character);
	ActionComponent->FindAction(HandleAction, EWeaponType::Yamato, EActionType::N_Front_Attack);
}

void UYamatoFrontHandler::SelfEnterHandle()
{
	Super::SelfEnterHandle();
}

void UYamatoFrontHandler::BreakEnterHandle()
{
	Super::BreakEnterHandle();
}

void UYamatoFrontHandler::CommonSignal_1()
{
	HandleAction.Index = 2;
	HandleAction.CurrentAnim = HandleAction.AnimArray[HandleAction.Index];
	ActionComponent->bToggleSignal = !ActionComponent->bToggleSignal;
}

void UYamatoFrontHandler::CommonSignal_2()
{
	CharacterMovementComponent->Velocity = FVector::Zero();
	CharacterMovementComponent->AddImpulse(Velocity, true);
	if(HitCharacter)
	{
		HitCharacter->GetCharacterMovement()->Velocity = FVector::Zero();
		HitCharacter->Damage(SelfCharacter,false,EActionType::Hit_Vector,Velocity);
	}
	GetWorld()->GetTimerManager().SetTimer(SetSafePlaceTimerHandle, this, &UYamatoFrontHandler::SetSafePlace, GetWorld()->DeltaTimeSeconds, true);
}

void UYamatoFrontHandler::CommonSignal_3()
{
	GetWorld()->GetTimerManager().ClearTimer(SetSafePlaceTimerHandle);
	if(HitCharacter)
	{
		HitCharacter->Damage(SelfCharacter,false,EActionType::Hit_Normal,FVector::Zero());
	}
}

void UYamatoFrontHandler::SetSafePlace()
{
	if(HitCharacter)
	{
		Start = HitCharacter->GetActorLocation();
		End = SelfCharacter->GetSafeClosePlace(HitCharacter->GetActorLocation());
		const FVector VInterpTo = FMath::VInterpTo(Start, End, GetWorld()->DeltaTimeSeconds, 10);
		HitCharacter->SetActorLocation(VInterpTo);
	}
}

void UYamatoFrontHandler::Exec()
{
	HandleAction.ActionLifeCycle = EActionLifeCycle::Exec;
	HandleAction.Index++;
	HandleAction.CurrentAnim = HandleAction.AnimArray[HandleAction.Index];
	ActionComponent->bToggleSignal = !ActionComponent->bToggleSignal;
	
	// UUPrintTool::Info(FString::Printf(TEXT("long press time = %f"), CurrentPressTime));
	// if(!bReleased && CurrentPressTime >= LongPressTime)
	// {
	// 	HandleAction.Index = 1;
	// 	HandleAction.CurrentAnim = HandleAction.AnimArray[HandleAction.Index];
	// 	ActionComponent->bToggleSignal = !ActionComponent->bToggleSignal;
	// }
}

void UYamatoFrontHandler::WhenHit(ABaseCharacter* BaseCharacter)
{
	if(HandleAction.ActionLifeCycle == EActionLifeCycle::Exec && !bReleased)
	{
		
		HitCharacter = BaseCharacter;
		HandleAction.Index = 3;
		FVector SafeClosePlace = SelfCharacter->GetSafeClosePlace(BaseCharacter->GetActorLocation());
		BaseCharacter->SetActorLocation(SafeClosePlace);
		HandleAction.CurrentAnim = HandleAction.AnimArray[HandleAction.Index];
		ActionComponent->bToggleSignal = !ActionComponent->bToggleSignal;
	}
}
