﻿// Fill out your copyright notice in the Description page of Project Settings.


#include "CommonSignal_1.h"

#include "Dmcv2/Dmc/ActionSystem/BaseActionComponent.h"
#include "Dmcv2/Dmc/ActionSystem/Handlers/BaseActionHandler.h"
#include "Dmcv2/Dmc/Character/BaseCharacter.h"

void UCommonSignal_1::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	if (const ABaseCharacter* BaseCharacter = Cast<ABaseCharacter>(MeshComp))
	{
		BaseCharacter->BaseActionComponent->CurrentHandler->CommonSignal_1();
	}
}
