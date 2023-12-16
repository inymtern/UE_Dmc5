// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Dmcv2/Dmc/ActionSystem/Handlers/Yamato/LongPressTriggerHandler.h"
#include "ForceEdgeBackFrontAfterHandler.generated.h"

/**
 * 
 */
UCLASS()
class DMCV2_API UForceEdgeBackFrontAfterHandler : public ULongPressTriggerHandler
{
	GENERATED_BODY()
public:
	
	
	virtual void Setup(ABaseCharacter* Character) override;

	virtual void Pre_2() override;

	virtual void FinishReleased() override;

	virtual void CommonSignal_1() override;
};
