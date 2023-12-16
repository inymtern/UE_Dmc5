// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Dmcv2/Dmc/ActionSystem/Handlers/FallToLanded.h"
#include "Dmcv2/Dmc/ActionSystem/Handlers/OrderExecHandler.h"
#include "FlashHandler.generated.h"

/**
 * 
 */
UCLASS()
class DMCV2_API UFlashHandler : public UOrderExecHandler, public IFallToLanded
{
	GENERATED_BODY()
public:

	
	UPROPERTY()
	FVector Start;
	UPROPERTY()
	FVector End;
	UPROPERTY()
	bool bEndIsAir = false;
	UPROPERTY()
	float Speed = 30;

	UPROPERTY()
	float MinDistance = 60;

	FTimerHandle OffsetTimerHandle;

	UPROPERTY()
	bool bFallingAndMiss = false;

	virtual bool BeforeEnter() override;
	
	virtual void Setup(ABaseCharacter* Character) override;

	virtual void Exec() override;

	virtual void After_1() override;

	virtual void After_3() override;

	virtual void Landed() override;

	virtual bool Break(UBaseActionHandler* SourceActionHandler) override;
	

	void Flash();
};
