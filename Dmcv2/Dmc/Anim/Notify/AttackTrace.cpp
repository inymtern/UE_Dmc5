// Fill out your copyright notice in the Description page of Project Settings.


#include "AttackTrace.h"

#include "Dmcv2/Dmc/Tools/CollisionTraceTool.h"

void UAttackTrace::NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration)
{
	Super::NotifyBegin(MeshComp, Animation, TotalDuration);
	if(!VergilCharacter && BaseCharacter)
	{
		VergilCharacter = Cast<AVergilCharacter>(BaseCharacter);
	}
}

void UAttackTrace::NotifyTick(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float FrameDeltaTime)
{
	if(!VergilCharacter) return;
	VergilCharacter->AttackTrace(HitBoxSize, bAttach, HitAction,  HitVelocity, FrontDistance, SilentDuration, false,bCloseCollision);
}

void UAttackTrace::NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	if(!VergilCharacter) return;
	VergilCharacter->AttackTraceEnd();
}


