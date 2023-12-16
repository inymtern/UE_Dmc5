// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotifyState.h"
#include "BaseNotifyState.generated.h"

class ABaseCharacter;
/**
 * 
 */
UCLASS()
class DMCV2_API UBaseNotifyState : public UAnimNotifyState
{
	GENERATED_BODY()
public:
	UPROPERTY()
	TObjectPtr<ABaseCharacter> BaseCharacter;

	virtual void NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration) override;
	virtual void NotifyTick(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float FrameDeltaTime) override;
	virtual void NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation) override;
};
