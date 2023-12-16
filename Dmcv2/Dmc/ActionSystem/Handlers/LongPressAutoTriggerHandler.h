// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseActionHandler.h"
#include "LongPressAutoTriggerHandler.generated.h"

/**
 * 
 */
UCLASS()
class DMCV2_API ULongPressAutoTriggerHandler : public UBaseActionHandler
{
	GENERATED_BODY()
public:

	UPROPERTY()
	bool bReleased = false;
	UPROPERTY()
	float LongPressTime = 0.25f;
	UPROPERTY()
	float CurrentPressTime = 0;

	virtual void Pre_1() override;

	virtual void SelfEnterHandle() override;

	virtual void BreakEnterHandle() override;
	
	virtual void Exec() override;

	virtual bool Break(UBaseActionHandler* SourceActionHandler) override;
};
