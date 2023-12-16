// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "BaseCharacter.generated.h"


class UBaseActionComponent;
enum EActionType : uint8;

namespace MyPlace
{
	UENUM(BlueprintType)
	enum ECustomDir
	{
		F,B,L,R,FL,FR,BL,BR
	};
}


UCLASS(Blueprintable)
class DMCV2_API ABaseCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	ABaseCharacter();
	UPROPERTY()
	TObjectPtr<UBaseActionComponent> BaseActionComponent;

	UPROPERTY()
	FVector2D MoveAxisValue; // 移动数据
	
	UPROPERTY()
	FVector2D FocusMoveAxisValue; // 锁定校准移动数据

	UPROPERTY()
	bool bFocusMode = false; // 锁定模式

	UPROPERTY()
	float CurrentMoveDirection; // 当前角度
	
	UPROPERTY()
	int SafeDistance = 200;
	
	UPROPERTY()
	float BasicPlayRate = 1;
	UPROPERTY()
	float DefaultGravity = 1.8f;
	UPROPERTY()
	float DefaultAirGravity = 0.15f;

	
	UPROPERTY()
	TObjectPtr<ABaseCharacter> FocusCharacter;

protected:
	virtual void BeginPlay() override;
	virtual void InitializeActionTable() ;
	virtual void InitializeActionMapping() ;
	
	

public:
	FVector GetRIndexPlace() const;
	FVector GetForwardVector(float Distance) const;
	FVector GetLocation(MyPlace::ECustomDir Direction, float Distance = 150) const;
	
	void TransitionMove(const FVector& End, const float Speed) ;

	void RotateTo(const ABaseCharacter* BaseCharacter);
	virtual void Damage(ABaseCharacter* SourceCharacter, bool bAttach, const EActionType& HitType, const FVector& HitVector, const float SilentDuration = 1.f, const float AirTime = 0);

	FVector GetSafeClosePlace(FVector SourceLocation) const; // 获取最近的安全位置

	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
};
