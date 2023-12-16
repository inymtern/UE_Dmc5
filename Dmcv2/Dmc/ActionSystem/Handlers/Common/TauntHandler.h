// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Dmcv2/Dmc/ActionSystem/Handlers/BaseActionHandler.h"
#include "TauntHandler.generated.h"

class ARotatorMiniGhostSwordActor;
/**
 * 
 */
UCLASS()
class DMCV2_API UTauntHandler : public UBaseActionHandler
{
	GENERATED_BODY()
public:
	UPROPERTY()
	ARotatorMiniGhostSwordActor* RotatorMiniGhostSwordActor;
	virtual void Setup(ABaseCharacter* Character) override;

	virtual void Exec() override;

	virtual void After_1() override;
};
