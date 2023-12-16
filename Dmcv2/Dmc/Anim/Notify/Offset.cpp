// Fill out your copyright notice in the Description page of Project Settings.


#include "Offset.h"

#include "Dmcv2/Dmc/Character/VergilCharacter.h"


void UOffset::NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration)
{
	Super::NotifyBegin(MeshComp, Animation, TotalDuration);
	if(BaseCharacter)
	{
		if(bCloseCollision)
		{
			BaseCharacter->SetActorEnableCollision(false);
		}
		VergilCharacter = Cast<AVergilCharacter>(BaseCharacter);
	}
}

void UOffset::NotifyTick(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float FrameDeltaTime)
{
	if(!BaseCharacter) return;
	if(Direction == D_Front)
	{
		const FVector ActorForwardVector = BaseCharacter->GetActorForwardVector();
		BaseCharacter->AddActorWorldOffset(ActorForwardVector * Rate);
		
	}else if(Direction == D_Back)
	{
		const FVector ActorForwardVector = BaseCharacter->GetActorForwardVector();
		BaseCharacter->AddActorWorldOffset(ActorForwardVector * Rate * -1);
	}
	if(bAttackTrace && VergilCharacter)
	{
		VergilCharacter->AttackTrace(FVector(200,150,150), bAttach, EActionType::Hit_Normal, FVector::Zero(), 80,1.5, bPushEnemy);
	}
}

void UOffset::NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	if(!BaseCharacter) return;
	if(bAttackTrace)
	{
		VergilCharacter->AttackTraceEnd();
	}
	
	if(bCloseCollision)
	{
		BaseCharacter->SetActorEnableCollision(true);
	}
}
