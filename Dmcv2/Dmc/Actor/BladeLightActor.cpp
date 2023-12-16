// Fill out your copyright notice in the Description page of Project Settings.


#include "BladeLightActor.h"

#include "Dmcv2/Dmc/Anim/Notify/AttackTrace.h"
#include "Dmcv2/Dmc/Character/BaseCharacter.h"


ABladeLightActor::ABladeLightActor(): SourceCharacter(nullptr)
{
	PrimaryActorTick.bCanEverTick = true;
}


void ABladeLightActor::BeginPlay()
{
	Super::BeginPlay();
	
}


void ABladeLightActor::Tick(float DeltaTime)
{
	if(bFire)
	{
		CurrentWaitTime += 0.1;
		if(CurrentWaitTime < TotalWaitTime) return;
		if(!bFront)
		{
			End = TargetCharacter->GetActorLocation();
		}
		const FVector VInterpTo = FMath::VInterpTo(Start, End, DeltaTime, FlySpeed);
		SetActorLocation(VInterpTo);
		Start = GetActorLocation();

		if(bFront)
		{
			const double EndDistance = FVector::Distance(Start, End);
			if(EndDistance < 100)
			{
				bFire = false;
				GetWorld()->GetTimerManager().SetTimer(DestroyTimeHandle, this, &ABladeLightActor::Destroyed, 0.3, false);
			}

			const int Distance = FVector::Distance(Start, TargetCharacter->GetActorLocation());
			if(Distance <= 270 && Distance % 30 == 0)
			{
				
				TargetCharacter->Damage(SourceCharacter,false,EActionType::Hit_Normal, FVector::Zero());
			}
		}else
		{
			const double Distance = FVector::Distance(Start, End);
			if(Distance < 100)
			{
				bFire = false;
				TargetCharacter->Damage(SourceCharacter,false,Hit_Vector, FVector(0, 0, 1200) );
				GetWorld()->GetTimerManager().SetTimer(DestroyTimeHandle, this, &ABladeLightActor::Destroyed, 0.3, false);
			}
		}
		
	}
}

void ABladeLightActor::Fire(ABaseCharacter* Source, ABaseCharacter* Target, const FRotator& Rotator, const float Speed, bool bIsFront)
{

	TargetCharacter = Target;
	SourceCharacter = Source;
	FlySpeed = Speed;
	Start = Source->GetActorLocation();
	SetActorRotation(Rotator);
	bFront = bIsFront;
	if(bFront)
	{
		End = Source->GetForwardVector(1500);
	}
	bFire = true;
}

void ABladeLightActor::Destroyed()
{
	GetWorld()->GetTimerManager().ClearTimer(DestroyTimeHandle);
	Super::Destroyed();
	GetWorld()->DestroyActor(this);
}
