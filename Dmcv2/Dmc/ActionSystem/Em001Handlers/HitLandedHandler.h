// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Dmcv2/Dmc/ActionSystem/Handlers/BaseHitHandler.h"
#include "HitLandedHandler.generated.h"

/**
 * 
 */
UCLASS()
class DMCV2_API UHitLandedHandler : public UBaseHitHandler
{
	GENERATED_BODY()
public:

	UPROPERTY()
	bool bNeedUp = false;
	virtual void Pre_1() override;
	virtual void Setup(ABaseCharacter* Character) override;

	virtual void CommonSignal_1() override;
	virtual void End() override;
};
