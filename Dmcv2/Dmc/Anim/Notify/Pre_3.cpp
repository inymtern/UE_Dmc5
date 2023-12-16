// Fill out your copyright notice in the Description page of Project Settings.


#include "Pre_3.h"

#include "Dmcv2/Dmc/ActionSystem/BaseActionComponent.h"
#include "Dmcv2/Dmc/ActionSystem/Handlers/BaseActionHandler.h"
#include "Dmcv2/Dmc/Character/BaseCharacter.h"

void UPre_3::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	if (const ABaseCharacter* BaseCharacter = Cast<ABaseCharacter>(MeshComp))
	{
		BaseCharacter->BaseActionComponent->CurrentHandler->Pre_3();
	}
}
