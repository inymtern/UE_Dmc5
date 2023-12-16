// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "RotatorMiniGhostSwordActor.generated.h"

class ABaseCharacter;

UCLASS()
class DMCV2_API ARotatorMiniGhostSwordActor : public AActor
{
	GENERATED_BODY()

public:
	ARotatorMiniGhostSwordActor();
	UPROPERTY()
	TObjectPtr<UStaticMeshComponent> StaticMeshComponent1;
	UPROPERTY()
	ABaseCharacter* SourceCharacter;

	UPROPERTY()
	bool bIsFinal = false;

protected:
	virtual void BeginPlay() override;

public:
	void Init(ABaseCharacter* MainCharacter);
	virtual void Tick(float DeltaTime) override;
};
