// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Dmcv2/Dmc/ActionSystem/Handlers/BaseHitHandler.h"
#include "HitGetUpHandler.generated.h"

/**
 * 
 */
UCLASS()
class DMCV2_API UHitGetUpHandler : public UBaseHitHandler
{
	GENERATED_BODY()
public:
	virtual void Setup(ABaseCharacter* Character) override;
};
