// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotify.h"
#include "After_1.generated.h"

/**
 * 
 */
UCLASS(BlueprintType)
class DMCV2_API UAfter_1 : public UAnimNotify
{
	GENERATED_BODY()
public:
	virtual void Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation) override;
};
