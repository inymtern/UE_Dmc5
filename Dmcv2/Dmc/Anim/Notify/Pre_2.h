// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotify.h"
#include "Pre_2.generated.h"

/**
 * 
 */
UCLASS(BlueprintType)
class DMCV2_API UPre_2 : public UAnimNotify
{
	GENERATED_BODY()
public:
	virtual void Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation) override;
};
