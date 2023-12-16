// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Dmcv2/Dmc/ActionSystem/Handlers/LongPressAutoTriggerHandler.h"
#include "Dmcv2/Dmc/ActionSystem/Handlers/Yamato/LongPressTriggerHandler.h"
#include "BeowulfBackHandler.generated.h"

/**
 * 
 */
UCLASS()
class DMCV2_API UBeowulfBackHandler : public ULongPressTriggerHandler
{
	GENERATED_BODY()
public:
	virtual void Setup(ABaseCharacter* Character) override;

	virtual void CommonSignal_1() override;

	virtual void FinishReleased() override;
};
