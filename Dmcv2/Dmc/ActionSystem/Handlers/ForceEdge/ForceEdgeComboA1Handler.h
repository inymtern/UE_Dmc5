// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Dmcv2/Dmc/ActionSystem/Handlers/ComboHandler.h"
#include "Dmcv2/Dmc/ActionSystem/Handlers/ManyClickManyTriggeredHandler.h"
#include "ForceEdgeComboA1Handler.generated.h"

/**
 * 
 */
UCLASS()
class DMCV2_API UForceEdgeComboA1Handler : public UBaseActionHandler
{
	GENERATED_BODY()
public:
	UPROPERTY()
	bool bCacheInput = false;
	
	virtual void Setup(ABaseCharacter* Character) override;

	virtual bool BeforeEnter() override;
	
	virtual void BreakEnterHandle() override;
	
	virtual void After_1() override;
};
