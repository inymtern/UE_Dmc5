// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Dmcv2/Dmc/ActionSystem/Handlers/ComboHandler.h"
#include "YamatoAirComboAHandler.generated.h"

/**
 * 
 */
UCLASS()
class DMCV2_API UYamatoAirComboAHandler : public UComboHandler
{
	GENERATED_BODY()
	
public:
	virtual void Setup(ABaseCharacter* Character) override;

	virtual bool BeforeEnter() override;

	virtual void Pre_1() override;

	virtual void After_3() override;

	virtual bool Break(UBaseActionHandler* SourceActionHandler) override;

	virtual bool WaitHandle() override;

	void KeepAir() const;
	void ResetAir() const;
};
