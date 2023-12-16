// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Dmcv2/Dmc/ActionSystem/Handlers/FallToLanded.h"
#include "Dmcv2/Dmc/ActionSystem/Handlers/OrderExecHandler.h"
#include "ForceEdgeAirBackHandler.generated.h"

/**
 * 
 */
UCLASS()
class DMCV2_API UForceEdgeAirBackHandler : public UOrderExecHandler, public IFallToLanded
{
	GENERATED_BODY()
public:
	
	UPROPERTY()
	FVector Speed = FVector(0,0, -800);
	
	virtual void Setup(ABaseCharacter* Character) override;

	virtual void Exec() override;

	virtual void After_1() override;

	virtual void Landed() override;
};
