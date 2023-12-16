// Fill out your copyright notice in the Description page of Project Settings.


#include "HitGetUpHandler.h"

void UHitGetUpHandler::Setup(ABaseCharacter* Character)
{
	Super::Setup(Character);
	ActionComponent->FindAction(HandleAction, EWeaponType::None, EActionType::Hit_Getup);
}
