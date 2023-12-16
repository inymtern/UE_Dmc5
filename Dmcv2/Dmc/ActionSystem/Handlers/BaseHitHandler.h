// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseActionHandler.h"
#include "BaseHitHandler.generated.h"

/**
 * 
 */
UCLASS()
class DMCV2_API UBaseHitHandler : public UBaseActionHandler
{
	GENERATED_BODY()
public:

	UPROPERTY()
	TObjectPtr<ABaseCharacter> SourceCharacter;
	
	virtual bool BeforeEnter() override;

};
