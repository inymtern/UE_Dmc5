// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Dmcv2/Dmc/ActionSystem/Handlers/LongPressAutoTriggerHandler.h"
#include "ForceEdgeBackHandler.generated.h"

/**
 * 
 */
UCLASS()
class DMCV2_API UForceEdgeBackHandler : public ULongPressAutoTriggerHandler
{
	GENERATED_BODY()
public:

	UPROPERTY()
	FVector Height = FVector(0,0,1600);

	
	virtual void Setup(ABaseCharacter* Character) override;

	virtual void CommonSignal_1() override;
	
};
