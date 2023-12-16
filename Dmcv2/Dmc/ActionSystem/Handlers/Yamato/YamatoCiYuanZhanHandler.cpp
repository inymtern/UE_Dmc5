// Fill out your copyright notice in the Description page of Project Settings.


#include "YamatoCiYuanZhanHandler.h"

#include "NiagaraComponent.h"
#include "NiagaraFunctionLibrary.h"
#include "NiagaraSystem.h"
#include "Dmcv2/Dmc/Character/BaseCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"


void UYamatoCiYuanZhanHandler::Setup(ABaseCharacter* Character)
{
	Super::Setup(Character);
	ActionComponent->FindAction(HandleAction, EWeaponType::Yamato, EActionType::N_Long_Press);
	NiagaraSystem = LoadObject<UNiagaraSystem>(nullptr, TEXT("NiagaraSystem'/Game/FX/ciyuanzhan/NS_Slash.NS_Slash'"));
}

bool UYamatoCiYuanZhanHandler::BeforeEnter()
{
	if(ActionComponent->CurrentHandler == this)
	{
		if(HandleAction.ActionLifeCycle >= EActionLifeCycle::After_1 && bIsPerfect)
		{
			SelfEnterHandle();
			return true;
		}
	}else
	{
		if(ActionComponent->CurrentHandler->Break(this))
		{
			BreakEnterHandle();
			return true;
		}
	}
	

	return false;
}

void UYamatoCiYuanZhanHandler::Pre_1()
{
	if(!BeforeEnter()) return;
	HandleAction.ActionLifeCycle = EActionLifeCycle::Pre_1;
	if(CharacterMovementComponent->IsFalling())
	{
		CharacterMovementComponent->Velocity = FVector::Zero();
		CharacterMovementComponent->GravityScale = 0;
		HandleAction.Index = bIsPerfect ? 3 : 2;
	}else
	{
		HandleAction.Index = bIsPerfect ? 1 : 0;
	}
	HandleAction.CurrentAnim = HandleAction.AnimArray[HandleAction.Index];
	ActionComponent->bToggleSignal = !ActionComponent->bToggleSignal;

}

void UYamatoCiYuanZhanHandler::Exec()
{
	HandleAction.ActionLifeCycle = EActionLifeCycle::Exec;
	if(!bIsPerfect)
	{
		HandleAction.Index = CharacterMovementComponent->IsFalling() ? 5 : 4;
	}else
	{
		HandleAction.Index = CharacterMovementComponent->IsFalling() ? 7 : 6;
	}
	
	HandleAction.CurrentAnim = HandleAction.AnimArray[HandleAction.Index];
	ActionComponent->bToggleSignal = !ActionComponent->bToggleSignal;

	if(SelfCharacter->FocusCharacter)
	{
		SelfCharacter->FocusCharacter->Damage(SelfCharacter,false,EActionType::Hit_Normal,FVector::Zero());
		const FVector ActorLocation = SelfCharacter->FocusCharacter->GetActorLocation();
		NiagaraComponent = UNiagaraFunctionLibrary::SpawnSystemAtLocation(GetWorld(),NiagaraSystem,ActorLocation);
		GetWorld()->GetTimerManager().SetTimer(NiagaraTimerHandle,this, &UYamatoCiYuanZhanHandler::ClearNiagara, 0.7f, false);
	}
}

void UYamatoCiYuanZhanHandler::After_1()
{
	HandleAction.ActionLifeCycle = EActionLifeCycle::After_1;
	HandleAction.Index = CharacterMovementComponent->IsFalling() ? 9 : 8;
	HandleAction.CurrentAnim = HandleAction.AnimArray[HandleAction.Index];
	ActionComponent->bToggleSignal = !ActionComponent->bToggleSignal;

	
}

void UYamatoCiYuanZhanHandler::CommonSignal_1()
{
	if(SelfCharacter->FocusCharacter)
	{
		SelfCharacter->FocusCharacter->Damage(SelfCharacter, false, EActionType::Hit_Normal,FVector::Zero(),0,0.20f);
	}
}

void UYamatoCiYuanZhanHandler::After_3()
{
	CharacterMovementComponent->GravityScale = SelfCharacter->DefaultGravity;
	Super::After_3();
}

bool UYamatoCiYuanZhanHandler::Break(UBaseActionHandler* SourceActionHandler)
{
	CharacterMovementComponent->GravityScale = SelfCharacter->DefaultGravity;
	return Super::Break(SourceActionHandler);
}

void UYamatoCiYuanZhanHandler::ClearNiagara()
{
	NiagaraComponent->DestroyComponent();
	GetWorld()->GetTimerManager().ClearTimer(NiagaraTimerHandle);
}
