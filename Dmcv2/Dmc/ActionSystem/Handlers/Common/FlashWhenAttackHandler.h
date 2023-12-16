// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Dmcv2/Dmc/ActionSystem/Handlers/OrderExecHandler.h"
#include "FlashWhenAttackHandler.generated.h"

/**
 * 
 */
UCLASS()
class DMCV2_API UFlashWhenAttackHandler : public UOrderExecHandler
{
	GENERATED_BODY()
public:

	FTimerHandle EndTimeHandle;

	UPROPERTY()
	float Duration = 0.2f;

	UPROPERTY()
	float AddTime = 0;

	UPROPERTY()
	FVector Start;
	
	UPROPERTY()
	FVector End;

	virtual bool BeforeEnter() override;
	
	virtual void Setup(ABaseCharacter* Character) override;

	virtual void Exec() override;

	virtual void After_1() override;

	void CallEndAnim();
	
	
	FVector CalcTargetBackLocation();
};
