// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseNotifyState.h"

#include "Dmcv2/Dmc/Character/BaseCharacter.h"

void UBaseNotifyState::NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration)
{
	AActor* Actor = MeshComp->GetOwner();
	if(!BaseCharacter)
	{
		BaseCharacter = Cast<ABaseCharacter>(Actor);
	}
}

void UBaseNotifyState::NotifyTick(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float FrameDeltaTime)
{
}

void UBaseNotifyState::NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
}
