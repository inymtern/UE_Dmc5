// Fill out your copyright notice in the Description page of Project Settings.


#include "GhostSwordActor.h"


AGhostSwordActor::AGhostSwordActor()
{
	PrimaryActorTick.bCanEverTick = true;
	StaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMeshComponent"));
	StaticMeshComponent->SetupAttachment(RootComponent);
	StaticMeshComponent->SetRelativeRotation(FRotator(0,-90,0));
	StaticMeshComponent->SetRelativeScale3D(FVector(0.5,0.5,0.5));
	static ConstructorHelpers::FObjectFinder<UStaticMesh> MeshAsset(TEXT("StaticMesh'/Game/Vergil_New/Mesh/ForceBlade/SM_ForceBlade.SM_ForceBlade'"));

	if(MeshAsset.Succeeded())
	{
		StaticMeshComponent->SetStaticMesh(MeshAsset.Object);
	}
}

void AGhostSwordActor::BeginPlay()
{
	Super::BeginPlay();
	
}

void AGhostSwordActor::Fire(bool Trace, bool RandomWaitTime, ABaseCharacter* OwnerChar, ABaseCharacter* Enemy,
	bool ApplyHit, EActionType HitType, FVector Scale)
{
	bFire = true;
	StaticMeshComponent->SetRelativeScale3D(Scale);
	bTrace = Trace;
	bRandomWaitTime = RandomWaitTime;
	OwnerCharacter = OwnerChar;
	TraceTarget = Enemy;
	if(bRandomWaitTime)
	{
		WaitTime = FMath::FRandRange(0.2, 0.8);
	}
	if(!bTrace)
	{
		FVector ActorLocation = GetActorLocation();
		ActorLocation.Z = 0;
		EndVector = ActorLocation;
	}
	HitAction = HitType;
	bApplyHit = ApplyHit;
}

void AGhostSwordActor::Tick(float DeltaTime)
{
	if(!bFire) return;
	CurrentAddTime += DeltaTime;
	if(CurrentAddTime < WaitTime) return;
	
	if(bTrace && TraceTarget) // 锁定目标时, 普通攻击/前
	{
		const FVector Start = GetActorLocation();
		
		const FVector End = TraceTarget->GetActorLocation();
		
		const FVector VInterpTo = FMath::VInterpTo(Start, End, DeltaTime, Speed);
		
		if(FVector::Distance(VInterpTo, End) <= 20)
		{
			if(bApplyHit)
			{
				TraceTarget->Damage(OwnerCharacter,false,HitAction,FVector::Zero());
			}
			Destroy();
		}else
		{
			SetActorLocation(VInterpTo);
		}
	}else // 后前
	{
		const FVector Start = GetActorLocation();
		const FVector VInterpTo = FMath::VInterpTo(Start, EndVector, DeltaTime, Speed);
		if(FVector::Distance(VInterpTo, EndVector) <= 20)
		{
			if(TraceTarget)
			{
				
				CurrentAddDestroyTime += DeltaTime;
				if(CurrentAddDestroyTime >= 2.f - WaitTime)
				{
					Destroy();
				}
			}
		}else
		{
			if(bApplyHit)
			{
				const FVector ActorLocation = TraceTarget->GetActorLocation();
				if(FVector::Distance(VInterpTo, ActorLocation) <= 30)
				{
					TraceTarget->Damage(OwnerCharacter, false, HitAction, FVector::Zero(), 1.5f);
				}
			}
			SetActorLocation(VInterpTo);
		}
	}
}

