// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Dmcv2/Dmc/ActionSystem/Handlers/BaseActionHandler.h"
#include "Dmcv2/Dmc/ActionSystem/Handlers/OrderExecHandler.h"
#include "ForceEdgeComboA3Handler.generated.h"

/**
 * 
 */
UCLASS()
class DMCV2_API UForceEdgeComboA3Handler : public UOrderExecHandler
{
	GENERATED_BODY()
public:
	virtual void Setup(ABaseCharacter* Character) override;

	virtual void CommonSignal_1() override;
};
