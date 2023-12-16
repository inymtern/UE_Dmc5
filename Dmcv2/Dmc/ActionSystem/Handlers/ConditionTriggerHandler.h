// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseActionHandler.h"
#include "LongPressAutoTriggerHandler.h"
#include "ConditionTriggerHandler.generated.h"

/**
 * 
 */
UCLASS()
class DMCV2_API UConditionTriggerHandler : public ULongPressAutoTriggerHandler
{
	GENERATED_BODY()
public:

	UPROPERTY()
	TObjectPtr<ABaseCharacter> HitCharacter;
	
	virtual void WhenHit(ABaseCharacter* BaseCharacter);
};
