// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BladeLightActor.generated.h"

class ABaseCharacter;

UCLASS(Blueprintable)
class DMCV2_API ABladeLightActor : public AActor
{
	GENERATED_BODY()

public:
	ABladeLightActor();


	UPROPERTY()
	TObjectPtr<ABaseCharacter> TargetCharacter;
	UPROPERTY()
	ABaseCharacter* SourceCharacter;

	

	UPROPERTY()
	float FlySpeed = 2.f;

	UPROPERTY()
	bool bFire = false;
	UPROPERTY()
	bool bFront = false;


	UPROPERTY()
	FVector Start;
	
	UPROPERTY()
	FVector End;

	UPROPERTY()
	float TotalWaitTime = 1.5;
	UPROPERTY()
	float CurrentWaitTime = 0;


	FTimerHandle DestroyTimeHandle;

protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;

	void Fire(ABaseCharacter* Source, ABaseCharacter* Target, const FRotator& Rotator, float Speed = 15.f, bool bIsFront = false);

	void Destroyed() override;
};
