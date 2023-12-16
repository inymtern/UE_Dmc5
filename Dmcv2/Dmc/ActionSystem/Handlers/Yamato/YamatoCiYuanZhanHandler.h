// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Dmcv2/Dmc/ActionSystem/Handlers/BaseActionHandler.h"
#include "Dmcv2/Dmc/ActionSystem/Handlers/OrderExecHandler.h"
#include "YamatoCiYuanZhanHandler.generated.h"

class UNiagaraComponent;
class UNiagaraSystem;
/**
 * 
 */
UCLASS()
class DMCV2_API UYamatoCiYuanZhanHandler : public UOrderExecHandler
{
	GENERATED_BODY()
public:

	UPROPERTY()
	bool bIsPerfect = false;
	UPROPERTY()
	TObjectPtr<UNiagaraSystem> NiagaraSystem;
	UPROPERTY()
	TObjectPtr<UNiagaraComponent> NiagaraComponent;
	FTimerHandle NiagaraTimerHandle;
	virtual void Setup(ABaseCharacter* Character) override;

	virtual bool BeforeEnter() override;

	virtual void Pre_1() override;

	virtual void Exec() override;

	virtual void After_1() override;

	virtual void CommonSignal_1() override;

	virtual void After_3() override;

	virtual bool Break(UBaseActionHandler* SourceActionHandler) override;

	void ClearNiagara();
	
};
