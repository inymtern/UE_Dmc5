﻿// Fill out your copyright notice in the Description page of Project Settings.


#include "After_2.h"

#include "Dmcv2/Dmc/ActionSystem/BaseActionComponent.h"
#include "Dmcv2/Dmc/ActionSystem/Handlers/BaseActionHandler.h"
#include "Dmcv2/Dmc/Character/BaseCharacter.h"

void UAfter_2::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	if (const ABaseCharacter* BaseCharacter = Cast<ABaseCharacter>(MeshComp))
	{
		BaseCharacter->BaseActionComponent->CurrentHandler->After_2();
	}
}
