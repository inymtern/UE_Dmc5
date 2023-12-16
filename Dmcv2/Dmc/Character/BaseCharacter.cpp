// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseCharacter.h"

#include "Dmcv2/Dmc/ActionSystem/BaseActionComponent.h"
#include "GameFramework/CharacterMovementComponent.h"


ABaseCharacter::ABaseCharacter()
{
	// PrimaryActorTick.bCanEverTick = true;
	BaseActionComponent = CreateDefaultSubobject<UBaseActionComponent>(TEXT("BaseActionComponent"));
}

void ABaseCharacter::BeginPlay()
{
	Super::BeginPlay();
	GetCharacterMovement()->GravityScale = DefaultGravity;
}

void ABaseCharacter::InitializeActionTable() 
{
}

void ABaseCharacter::InitializeActionMapping() 
{
}

FVector ABaseCharacter::GetRIndexPlace() const
{
	return GetMesh()->GetSocketLocation(FName("R_Index_Socket"));
}

FVector ABaseCharacter::GetForwardVector(const float Distance) const
{
	const FVector ActorLocation = GetActorLocation();
	return ActorLocation + GetActorForwardVector() * Distance;
}

FVector ABaseCharacter::GetLocation(const MyPlace::ECustomDir Direction, const float Distance) const
{
	const FVector ActorLocation = GetActorLocation();
	const FVector ActorForwardVector = GetActorForwardVector();
	const FVector ActorRightVector = GetActorRightVector();
	
	switch (Direction)
	{
	case MyPlace::F:
		{
			return ActorLocation + ActorForwardVector * Distance;
		}
	case MyPlace::B:
		{
			return ActorLocation + ActorForwardVector * Distance * -1;
		}
	case MyPlace::L:
		{
			return ActorLocation + ActorRightVector * Distance * -1;
		}
	case MyPlace::R:
		{
			return ActorLocation + ActorRightVector * Distance;
		}
	case MyPlace::FR:
		{
			const FVector Temp = (ActorRightVector + ActorForwardVector).GetSafeNormal();
			return ActorLocation + Temp * Distance;
		}
	case MyPlace::FL:
		{
			const FVector Temp = (ActorRightVector * -1 + ActorForwardVector).GetSafeNormal();
			return ActorLocation + Temp * Distance;
		}
	case MyPlace::BR:
		{
			const FVector Temp = (ActorRightVector + ActorForwardVector * -1).GetSafeNormal();
			return ActorLocation + Temp * Distance;
		}
	case MyPlace::BL:
		{
			const FVector Temp = (ActorRightVector * -1 + ActorForwardVector * -1).GetSafeNormal();
			return ActorLocation + Temp * Distance;
		}
	default:
		{
			return ActorLocation + ActorForwardVector * Distance;
		};
	}
}



void ABaseCharacter::TransitionMove(const FVector& End, const float Speed) 
{
	const FVector VInterpTo = FMath::VInterpTo(GetActorLocation(), End, GetWorld()->DeltaTimeSeconds, Speed);
	SetActorLocation(VInterpTo);
}



void ABaseCharacter::RotateTo(const ABaseCharacter* BaseCharacter)
{
	if(BaseCharacter)
	{
		const FVector ActorLocation = GetActorLocation();
		FVector TargetLocation = BaseCharacter->GetActorLocation();
		TargetLocation.Z = ActorLocation.Z;
		SetActorRotation((TargetLocation - ActorLocation).Rotation());
	}
}


void ABaseCharacter::Damage(ABaseCharacter* SourceCharacter,  bool bAttach, const EActionType& HitType, const FVector& HitVector, const float SilentDuration, const float AirTime)
{
}

FVector ABaseCharacter::GetSafeClosePlace(FVector SourceLocation) const
{
	const FVector SelfLocation = GetActorLocation();
	SourceLocation.Z = SelfLocation.Z;
	const FVector LookAt = (SourceLocation - SelfLocation).GetSafeNormal();
	FVector Res = (LookAt * SafeDistance + SelfLocation);
	Res.Z = SelfLocation.Z + 30;
	return Res;
}

void ABaseCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ABaseCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

