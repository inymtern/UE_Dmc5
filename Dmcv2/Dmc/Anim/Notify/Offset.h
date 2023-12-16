// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseNotifyState.h"
#include "Animation/AnimNotifies/AnimNotifyState.h"
#include "Dmcv2/Dmc/Character/BaseCharacter.h"
#include "Offset.generated.h"
/**
 * 
 */

class AVergilCharacter;

UENUM(BlueprintType)
enum ECustomDir
{
	D_Front,
	D_Back
	
};

UCLASS(BlueprintType)
class DMCV2_API UOffset : public UBaseNotifyState
{
	GENERATED_BODY()
public:

	UPROPERTY()
	TObjectPtr<AVergilCharacter> VergilCharacter;
	
	UPROPERTY(EditAnywhere)
	TEnumAsByte<ECustomDir> Direction;

	UPROPERTY(EditAnywhere)
	float Rate = 10.f;

	UPROPERTY(EditAnywhere)
	bool bAttackTrace = false;
	UPROPERTY(EditAnywhere)
	bool bCloseCollision = true;
	UPROPERTY(EditAnywhere)
	bool bPushEnemy = false;
	UPROPERTY(EditAnywhere)
	bool bAttach = false;
	virtual void NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration) override;
	virtual void NotifyTick(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float FrameDeltaTime) override;
	virtual void NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation) override;
};
