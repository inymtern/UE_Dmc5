// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "Dmcv2/Dmc/ActionSystem/BaseActionComponent.h"
#include "BaseCharacterAnimInstance.generated.h"

struct FAnim;
class ABaseCharacter;
/**
 * 
 */
UCLASS(Blueprintable)
class DMCV2_API UBaseCharacterAnimInstance : public UAnimInstance
{
	GENERATED_BODY()
public:

	UPROPERTY()
	TObjectPtr<ABaseCharacter> BaseCharacter;
	UPROPERTY(BlueprintReadOnly)
	FAnim CurrentAnim;
	UPROPERTY(BlueprintReadOnly)
	TEnumAsByte<EActionLifeCycle> CurrentActionLifeCycle = EActionLifeCycle::End;
	UPROPERTY(BlueprintReadOnly)
	FVector2D MoveAxisValue;

	UPROPERTY(BlueprintReadOnly)
	FVector2D FocusMoveAxisValue;
	UPROPERTY(BlueprintReadOnly)
	bool bToggleSignal;
	UPROPERTY(BlueprintReadOnly)
	bool bFocusMode = false;
	UPROPERTY(BlueprintReadOnly)
	float CurrentMoveDirection;
	UPROPERTY(BlueprintReadOnly)
	bool bIsFalling = false;
	UPROPERTY(BlueprintReadOnly)
	float BasicPlayRate = 1;

	
	virtual void NativeInitializeAnimation() override;
	virtual void NativeThreadSafeUpdateAnimation(float DeltaSeconds) override;
	virtual bool HandleNotify(const FAnimNotifyEvent& AnimNotifyEvent) override;
};
