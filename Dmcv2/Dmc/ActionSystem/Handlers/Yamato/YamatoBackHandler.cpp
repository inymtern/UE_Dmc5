// Fill out your copyright notice in the Description page of Project Settings.


#include "YamatoBackHandler.h"

#include "Dmcv2/Dmc/Character/BaseCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"

void UYamatoBackHandler::Setup(ABaseCharacter* Character)
{
	Super::Setup(Character);
	ActionComponent->FindAction(HandleAction, EWeaponType::Yamato, EActionType::N_Back_Attack);
}

void UYamatoBackHandler::CommonSignal_1()
{
	SelfCharacter->GetCharacterMovement()->AddImpulse(Height, true);
}
