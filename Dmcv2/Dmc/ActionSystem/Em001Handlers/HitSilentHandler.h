// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Dmcv2/Dmc/ActionSystem/Handlers/BaseHitHandler.h"
#include "HitSilentHandler.generated.h"

/**
 * 
 */
UCLASS()
class DMCV2_API UHitSilentHandler : public UBaseHitHandler
{
	GENERATED_BODY()
public:

	UPROPERTY()
	bool bFinish = false;
	UPROPERTY()
	float PlayRate = 0.1f;
	UPROPERTY()
	float Duration = 1.f;

	FTimerHandle SilentTimerHandle;
	
	virtual void Setup(ABaseCharacter* Character) override;

	virtual void Pre_1() override;

	virtual void CommonSignal_2() override;
	
	virtual bool Break(UBaseActionHandler* SourceActionHandler) override;

	void EnterSilent();
	void BreakSilent();
};
