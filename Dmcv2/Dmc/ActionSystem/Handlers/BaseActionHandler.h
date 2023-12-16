// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Dmcv2/Dmc/ActionSystem/BaseActionComponent.h"
#include "UObject/Object.h"
#include "BaseActionHandler.generated.h"

class UCharacterMovementComponent;
struct FAction;
/**
 * 
 */
UCLASS()
class DMCV2_API UBaseActionHandler : public UObject
{
	GENERATED_BODY()
public:
	UBaseActionHandler();
	UPROPERTY()
	TObjectPtr<ABaseCharacter> SelfCharacter;
	UPROPERTY()
	TObjectPtr<UBaseActionComponent> ActionComponent;
	UPROPERTY()
	TObjectPtr<UCharacterMovementComponent> CharacterMovementComponent;
	UPROPERTY()
	FAction HandleAction;

	virtual void Setup(ABaseCharacter* Character);

	virtual void SelfEnterHandle();
	virtual void BreakEnterHandle();

	virtual bool BeforeEnter();
	
	virtual void Pre_1();
	virtual void Pre_2();
	virtual void Pre_3();

	virtual void Exec();

	virtual void After_1();
	virtual void After_2();
	virtual void After_3();

	virtual void ResetCombo();

	virtual void End();

	virtual void CommonSignal_1();
	virtual void CommonSignal_2();
	virtual void CommonSignal_3();
	

	virtual bool Break(UBaseActionHandler* SourceActionHandler);
};
