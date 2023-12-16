// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Dmcv2/Dmc/ActionSystem/Handlers/BaseActionHandler.h"
#include "Dmcv2/Dmc/ActionSystem/Handlers/ConditionTriggerHandler.h"
#include "Dmcv2/Dmc/ActionSystem/Handlers/LongPressAutoTriggerHandler.h"
#include "YamatoFrontHandler.generated.h"

/**
 * 
 */
UCLASS()
class DMCV2_API UYamatoFrontHandler : public UConditionTriggerHandler
{
	GENERATED_BODY()
public:

	UPROPERTY()
	FVector Velocity = FVector(0,0,1600);

	UPROPERTY()
	FVector Start;

	UPROPERTY()
	FVector End;
	
	FTimerHandle SetSafePlaceTimerHandle;
	
	virtual void Setup(ABaseCharacter* Character) override;

	virtual void SelfEnterHandle() override;

	virtual void BreakEnterHandle() override;

	virtual void CommonSignal_1() override;

	virtual void CommonSignal_2() override;
	virtual void CommonSignal_3() override;

	void SetSafePlace();

	virtual void Exec() override;

	virtual void WhenHit(ABaseCharacter* BaseCharacter) override;
};
