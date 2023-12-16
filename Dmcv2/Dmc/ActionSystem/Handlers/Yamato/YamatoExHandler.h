// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Dmcv2/Dmc/ActionSystem/Handlers/OrderExecHandler.h"
#include "YamatoExHandler.generated.h"

class UNiagaraSystem;
/**
 * 
 */
UCLASS()
class DMCV2_API UYamatoExHandler : public UOrderExecHandler
{
	GENERATED_BODY()
public:

	UYamatoExHandler();
	FTimerHandle EndTimeHandle;
	UPROPERTY()
	TObjectPtr<UNiagaraSystem> NiagaraSystem;

	
	virtual void Setup(ABaseCharacter* Character) override;

	virtual void Pre_1() override;

	virtual void Exec() override;

	virtual void After_1() override;

	virtual void After_3() override;

	void CallEndAnim();
};
