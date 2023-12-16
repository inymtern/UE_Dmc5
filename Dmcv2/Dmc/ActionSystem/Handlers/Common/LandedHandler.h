// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Dmcv2/Dmc/ActionSystem/Handlers/BaseActionHandler.h"
#include "LandedHandler.generated.h"

/**
 * 
 */
UCLASS()
class DMCV2_API ULandedHandler : public UBaseActionHandler
{
	GENERATED_BODY()
public:
	virtual void Setup(ABaseCharacter* Character) override;

	virtual bool BeforeEnter() override;

	virtual void Pre_1() override;

	
};
