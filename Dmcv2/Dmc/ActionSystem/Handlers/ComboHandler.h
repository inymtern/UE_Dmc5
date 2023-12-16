// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseActionHandler.h"
#include "UObject/Object.h"
#include "ComboHandler.generated.h"

/**
 * 
 */
UCLASS()
class DMCV2_API UComboHandler : public UBaseActionHandler
{
	GENERATED_BODY()

public:

	UPROPERTY()
	bool bCacheInput = false;

	
	virtual void Setup(ABaseCharacter* Character) override;

	virtual void SelfEnterHandle() override;
	virtual void BreakEnterHandle() override;
	virtual bool BeforeEnter() override;
	virtual void Pre_1() override;
	virtual void Pre_2() override;
	virtual void Pre_3() override;
	virtual void Exec() override;
	virtual void After_1() override;
	virtual void After_2() override;
	virtual void After_3() override;
	virtual void End() override;
	virtual void CommonSignal_1() override;
	virtual void CommonSignal_2() override;
	virtual void CommonSignal_3() override;
	virtual bool Break(UBaseActionHandler* SourceActionHandler) override;

	virtual bool WaitHandle();
};
