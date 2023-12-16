// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Dmcv2/Dmc/ActionSystem/Handlers/ComboHandler.h"
#include "YamatoComboAHandler.generated.h"

/**
 * 
 */
UCLASS()
class DMCV2_API UYamatoComboAHandler : public UComboHandler
{
	GENERATED_BODY()
public:
	virtual void Setup(ABaseCharacter* Character) override;

	virtual bool BeforeEnter() override;

};
