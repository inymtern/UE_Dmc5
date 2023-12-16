// Fill out your copyright notice in the Description page of Project Settings.


#include "YamatoComboA2Handler.h"

void UYamatoComboA2Handler::Setup(ABaseCharacter* Character)
{
	Super::Setup(Character);
	ActionComponent->FindAction(HandleAction, EWeaponType::Yamato, EActionType::N_Combo_A2);
}


