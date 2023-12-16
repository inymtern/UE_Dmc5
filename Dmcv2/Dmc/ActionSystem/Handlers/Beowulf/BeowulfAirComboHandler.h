// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Dmcv2/Dmc/ActionSystem/Handlers/BaseActionHandler.h"
#include "Dmcv2/Dmc/ActionSystem/Handlers/FallToLanded.h"
#include "BeowulfAirComboHandler.generated.h"

/**
 * 
 */
UCLASS()
class DMCV2_API UBeowulfAirComboHandler : public UBaseActionHandler, public IFallToLanded
{
	GENERATED_BODY()
public:
	virtual void Setup(ABaseCharacter* Character) override;

	virtual void Pre_1() override;

	virtual void CommonSignal_1() override;

	virtual void Exec() override;

	virtual bool Break(UBaseActionHandler* SourceActionHandler) override;

	FVector CalcStarFallDirection() const;

	virtual void Landed() override;
	
};
