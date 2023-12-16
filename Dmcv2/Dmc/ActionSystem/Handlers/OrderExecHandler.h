// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseActionHandler.h"
#include "OrderExecHandler.generated.h"

/**
 * 
 */
UCLASS()
class DMCV2_API UOrderExecHandler : public UBaseActionHandler
{
	GENERATED_BODY()
public:
	virtual void Pre_1() override;
	virtual void Exec() override;
	virtual void After_1() override;
};
