// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Dmcv2/Dmc/Anim/Notify/AttackTrace.h"
#include "GameFramework/Actor.h"
#include "GhostSwordActor.generated.h"

class ABaseCharacter;

UCLASS()
class DMCV2_API AGhostSwordActor : public AActor
{
	GENERATED_BODY()

public:
	AGhostSwordActor();
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TObjectPtr<UStaticMeshComponent> StaticMeshComponent;

	UPROPERTY(EditAnywhere)
	float Speed = 20.f; 
	UPROPERTY()
	bool bFire = false;
	UPROPERTY()
	bool bTrace = false; 
	UPROPERTY()
	bool bApplyHit = true; 
	UPROPERTY()
	bool bRandomWaitTime = false;

	UPROPERTY()
	TEnumAsByte<EActionType> HitAction = EActionType::Hit_Normal; // 受击类型

	UPROPERTY()
	FVector EndVector; // 结束位置

	UPROPERTY()
	float WaitTime = 0.2f; // 默认等待时间

	UPROPERTY()
	float CurrentAddTime = 0.f;

	UPROPERTY()
	float CurrentAddDestroyTime = 0.f;
	
	UPROPERTY()
	TObjectPtr<ABaseCharacter> TraceTarget;
	
	UPROPERTY()
	TObjectPtr<ABaseCharacter> OwnerCharacter;

	
	
protected:
	virtual void BeginPlay() override;

public:


	virtual void Fire(bool Trace, bool RandomWaitTime, ABaseCharacter* OwnerChar, ABaseCharacter* Enemy, bool ApplyHit = true,  EActionType HitType = EActionType::Hit_Normal, FVector Scale = FVector(0.5,0.5,0.5));
	
	virtual void Tick(float DeltaTime) override;
};
