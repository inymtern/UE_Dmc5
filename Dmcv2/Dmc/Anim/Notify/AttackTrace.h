// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseNotifyState.h"
#include "Dmcv2/Dmc/Character/VergilCharacter.h"
#include "AttackTrace.generated.h"

enum EActionType : uint8;
/**
 * 
 */
UCLASS(BlueprintType)
class DMCV2_API UAttackTrace : public UBaseNotifyState
{
	GENERATED_BODY()

	
public:

	UPROPERTY()
	TObjectPtr<AVergilCharacter> VergilCharacter;
	
	UPROPERTY(EditAnywhere)
	bool bAttach = true;

	UPROPERTY(EditAnywhere)
	TEnumAsByte<EActionType> HitAction = EActionType::Hit_Normal;
	
	UPROPERTY(EditAnywhere)
	FVector HitBoxSize = FVector(200, 150, 100);

	UPROPERTY(EditAnywhere)
	FVector HitVelocity = FVector::Zero();

	UPROPERTY(EditAnywhere)
	float FrontDistance = 150;

	UPROPERTY(EditAnywhere)
	float SilentDuration  = 1.5f;

	UPROPERTY(EditAnywhere)
	bool bCloseCollision = false;
	
	
	virtual void NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration) override;
	virtual void NotifyTick(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float FrameDeltaTime) override;
	virtual void NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation) override;
};
