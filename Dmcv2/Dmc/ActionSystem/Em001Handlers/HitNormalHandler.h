// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Dmcv2/Dmc/ActionSystem/Handlers/BaseHitHandler.h"
#include "HitNormalHandler.generated.h"

/**
 * 
 */
UCLASS()
class DMCV2_API UHitNormalHandler : public UBaseHitHandler
{
	GENERATED_BODY()
public:
	UPROPERTY()
	float AirTime = 0;


	FTimerHandle AirTimerHandle;
	
	virtual void Setup(ABaseCharacter* Character) override;

	virtual void Pre_1() override;

	virtual void CommonSignal_1() override;

	virtual bool Break(UBaseActionHandler* SourceActionHandler) override;
};
