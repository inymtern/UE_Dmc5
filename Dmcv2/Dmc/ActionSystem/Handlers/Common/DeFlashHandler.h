// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Dmcv2/Dmc/ActionSystem/Handlers/FallToLanded.h"
#include "Dmcv2/Dmc/ActionSystem/Handlers/OrderExecHandler.h"
#include "DeFlashHandler.generated.h"

/**
 * 
 */
UCLASS()
class DMCV2_API UDeFlashHandler : public UOrderExecHandler, public IFallToLanded
{
	GENERATED_BODY()
public:
	virtual void Setup(ABaseCharacter* Character) override;

	UPROPERTY()
	FVector Start;

	UPROPERTY()
	FVector End;

	UPROPERTY()
	float MinDistance = 10;

	UPROPERTY()
	float Speed = 30;

	UPROPERTY()
	float BackDistance = 500;
	
	UPROPERTY()
	float DownSpeed = 3000;

	FTimerHandle FlashTimerHandle;

	virtual bool BeforeEnter() override;

	virtual void Exec() override;

	virtual void After_1() override;

	virtual void Landed() override;

	void DeFlash();

	FVector CalcBackLocation() const;
};
