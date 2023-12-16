// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Dmcv2/Dmc/ActionSystem/Handlers/ComboHandler.h"
#include "Dmcv2/Dmc/ActionSystem/Handlers/ManyClickManyTriggeredHandler.h"
#include "YamatoComboA2Handler.generated.h"

/**
 * 
 */
UCLASS()
class DMCV2_API UYamatoComboA2Handler : public UManyClickManyTriggeredHandler
{
	GENERATED_BODY()
public:
	virtual void Setup(ABaseCharacter* Character) override;


	
};
