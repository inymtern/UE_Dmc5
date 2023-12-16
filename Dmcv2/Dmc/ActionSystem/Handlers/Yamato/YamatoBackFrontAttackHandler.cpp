// Fill out your copyright notice in the Description page of Project Settings.


#include "YamatoBackFrontAttackHandler.h"

#include "AITestsCommon.h"
#include "Dmcv2/Dmc/Character/BaseCharacter.h"
#include "Dmcv2/Dmc/Character/VergilCharacter.h"

void UYamatoBackFrontAttackHandler::Setup(ABaseCharacter* Character)
{
	Super::Setup(Character);
	ActionComponent->FindAction(HandleAction, EWeaponType::Yamato, EActionType::N_Back_Front_Attack);
}

// void UYamatoBackFrontAttackHandler::CommonSignal_1()
// {
// 	VergilCharacter = Cast<AVergilCharacter>(SelfCharacter);
// 	GetWorld()->GetTimerManager().SetTimer(TraceTimerHandle, this, &UYamatoBackFrontAttackHandler::AttackTrace, GetWorld()->DeltaTimeSeconds,true);
// }
//
// void UYamatoBackFrontAttackHandler::CommonSignal_2()
// {
// 	GetWorld()->GetTimerManager().ClearTimer(TraceTimerHandle);
// 	VergilCharacter->AttackTraceEnd();
// }
//
// void UYamatoBackFrontAttackHandler::AttackTrace()
// {
// 	VergilCharacter->AttackTrace(Size, false, EActionType::Hit_Silent, FVector::Zero(),150);
// }
