// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Dmcv2/Dmc/ActionSystem/Handlers/OrderExecHandler.h"
#include "BeowulfFrontHandler.generated.h"

/**
 * 
 */
UCLASS()
class DMCV2_API UBeowulfFrontHandler : public UOrderExecHandler
{
	GENERATED_BODY()
public:
	virtual void Setup(ABaseCharacter* Character) override;

	virtual void Exec() override;
	virtual void CommonSignal_1() override;
	virtual void After_1() override;
};
