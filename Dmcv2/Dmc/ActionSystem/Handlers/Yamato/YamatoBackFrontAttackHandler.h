// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Dmcv2/Dmc/ActionSystem/Handlers/BaseActionHandler.h"
#include "YamatoBackFrontAttackHandler.generated.h"

class AVergilCharacter;
/**
 * 
 */
UCLASS()
class DMCV2_API UYamatoBackFrontAttackHandler : public UBaseActionHandler
{
	GENERATED_BODY()
public:

	FTimerHandle TraceTimerHandle;

	UPROPERTY()
	TObjectPtr<AVergilCharacter> VergilCharacter;
	// UPROPERTY()
	// FVector Size = FVector(350, 200, 100);
	
	virtual void Setup(ABaseCharacter* Character) override;

	// virtual void CommonSignal_1() override;
	//
	// virtual void CommonSignal_2() override;

	// void AttackTrace();
};
