// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Dmcv2/Dmc/ActionSystem/Handlers/BaseActionHandler.h"
#include "Dmcv2/Dmc/ActionSystem/Handlers/FallToLanded.h"
#include "JumpHandler.generated.h"

/**
 * 
 */
UCLASS()
class DMCV2_API UJumpHandler : public UBaseActionHandler, public IFallToLanded
{
	GENERATED_BODY()
public:

	UPROPERTY()
	FVector Velocity = FVector(0,0,1200);
	
	UPROPERTY()
	FVector DeVelocity = FVector(0,0,-5000);

	UPROPERTY()
	float Duration = 0.3f;

	UPROPERTY()
	bool bSoon = false;

	FTimerHandle SoonTimerHandle;

	virtual void Setup(ABaseCharacter* Character) override;

	virtual bool BeforeEnter() override;

	virtual void Pre_1() override;
	
	
	virtual void Exec() override;

	virtual void After_1() override;


	void Landed() override;
};
