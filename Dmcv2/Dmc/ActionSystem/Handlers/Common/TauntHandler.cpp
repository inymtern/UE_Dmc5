// Fill out your copyright notice in the Description page of Project Settings.


#include "TauntHandler.h"

#include "Dmcv2/Dmc/Actor/RotatorMiniGhostSwordActor.h"
#include "Dmcv2/Dmc/Character/BaseCharacter.h"

void UTauntHandler::Setup(ABaseCharacter* Character)
{
	Super::Setup(Character);
	ActionComponent->FindAction(HandleAction, EWeaponType::None, EActionType::N_Taunt);
}

void UTauntHandler::Exec()
{
	Super::Exec();
	RotatorMiniGhostSwordActor = GetWorld()->SpawnActor<ARotatorMiniGhostSwordActor>(SelfCharacter->GetRIndexPlace(), FRotator::ZeroRotator);
	RotatorMiniGhostSwordActor->Init(SelfCharacter);
}

void UTauntHandler::After_1()
{
	Super::After_1();
	if(RotatorMiniGhostSwordActor)
	{
		RotatorMiniGhostSwordActor->bIsFinal = true;
	}
}
