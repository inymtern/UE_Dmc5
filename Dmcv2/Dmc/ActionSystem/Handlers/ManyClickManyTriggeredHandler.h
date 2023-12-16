// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseActionHandler.h"
#include "ManyClickManyTriggeredHandler.generated.h"

/**
 * 
 */
UCLASS()
class DMCV2_API UManyClickManyTriggeredHandler : public UBaseActionHandler
{
	GENERATED_BODY()
public:

	UPROPERTY()
	int MaxTriggerCount = 5;
	UPROPERTY()
	int CurrentTriggerCount = 0;
	UPROPERTY()
	bool bSaved = false;

	virtual bool BeforeEnter() override;
	virtual void Exec() override;
	virtual void BreakEnterHandle() override;

	virtual void After_1() override;

	virtual bool Trigger();
	
	virtual void EnterNext();

	

	
};

inline void UManyClickManyTriggeredHandler::BreakEnterHandle()
{
	Super::BreakEnterHandle();
	bSaved = false;
	CurrentTriggerCount = 0;
}


