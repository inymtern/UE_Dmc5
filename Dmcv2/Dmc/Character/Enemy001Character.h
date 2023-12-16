// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseCharacter.h"
#include "Dmcv2/Dmc/ActionSystem/BaseActionComponent.h"
#include "Enemy001Character.generated.h"

UCLASS(Blueprintable)
class DMCV2_API AEnemy001Character : public ABaseCharacter
{
	GENERATED_BODY()

public:
	AEnemy001Character();

protected:
	virtual void BeginPlay() override;

	void InitComponent() const;
	virtual void InitializeActionTable()  override;
	virtual void InitializeActionMapping()  override;
	virtual void Damage(ABaseCharacter* SourceCharacter, bool bAttach, const EActionType& HitType, const FVector& HitVector, const float SilentDuration = 1.f, const float AirTime = 0) override;

	virtual void Landed(const FHitResult& Hit) override;
public:
	virtual void Tick(float DeltaTime) override;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
};

inline void AEnemy001Character::Landed(const FHitResult& Hit)
{
	BaseActionComponent->FindActionHandlerExec(EWeaponType::None, EActionType::Hit_Land);
}
