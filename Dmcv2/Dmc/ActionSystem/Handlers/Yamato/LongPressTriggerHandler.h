// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Dmcv2/Dmc/ActionSystem/Handlers/BaseHitHandler.h"
#include "Dmcv2/Dmc/ActionSystem/Handlers/LongPressAutoTriggerHandler.h"
#include "LongPressTriggerHandler.generated.h"

/**
 * 
 */
UCLASS()
class DMCV2_API ULongPressTriggerHandler : public ULongPressAutoTriggerHandler
{
	GENERATED_BODY()
public:
	UPROPERTY()
	bool bCrossPre2 = false;

	virtual void Exec() override;
	
	virtual void Pre_2() override;
	virtual void Pre_3() override;

	virtual void FinishReleased();
};
