// Fill out your copyright notice in the Description page of Project Settings.


#include "RotatorMiniGhostSwordActor.h"

#include "Dmcv2/Dmc/Anim/Notify/AttackTrace.h"
#include "Dmcv2/Dmc/Character/BaseCharacter.h"
#include "Dmcv2/Dmc/Tools/CollisionTraceTool.h"


ARotatorMiniGhostSwordActor::ARotatorMiniGhostSwordActor()
{
	PrimaryActorTick.bCanEverTick = true;

	StaticMeshComponent1 = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMeshComponent1"));
	StaticMeshComponent1->SetRelativeScale3D(FVector(0.5,0.5,0.5));
	static ConstructorHelpers::FObjectFinder<UStaticMesh> StaticMeshAsset(TEXT("StaticMesh'/Game/Vergil_New/Mesh/ForceBlade/SM_ForceBlade.SM_ForceBlade'"));

	if(StaticMeshAsset.Succeeded())
	{
		StaticMeshComponent1->SetStaticMesh(StaticMeshAsset.Object);
	}

}

void ARotatorMiniGhostSwordActor::BeginPlay()
{
	Super::BeginPlay();
}

void ARotatorMiniGhostSwordActor::Init(ABaseCharacter* MainCharacter)
{
	SourceCharacter = MainCharacter;
}



void ARotatorMiniGhostSwordActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	AddActorWorldRotation(FRotator(0,15,0));

	if(GetActorRotation().Yaw == 0)
	{
		if (TArray<FOverlapResult> Result; UCollisionTraceTool::BoxOverlapTrace(GetWorld(), Result, GetActorLocation(),FVector(80,80,20),FRotator::ZeroRotator))
		{
			for (FOverlapResult OverlapResult : Result)
			{
				AActor* Actor = OverlapResult.GetActor();
				if (ABaseCharacter* EnemyCharacter = Cast<ABaseCharacter>(Actor))
				{
					EnemyCharacter->Damage(SourceCharacter, false,EActionType::Hit_Normal, FVector::Zero());
				}
			}
		}
	}

	if(bIsFinal)
	{
		if (TArray<FOverlapResult> Result; UCollisionTraceTool::BoxOverlapTrace(GetWorld(), Result, GetActorLocation(),FVector(80,80,50)))
		{
			for (FOverlapResult OverlapResult : Result)
			{
				AActor* Actor = OverlapResult.GetActor();
				if (ABaseCharacter* EnemyCharacter = Cast<ABaseCharacter>(Actor))
				{
					EnemyCharacter->Damage(SourceCharacter, false,EActionType::Hit_Vector, FVector(0,0,1600));
				}
			}
		}
		GetWorld()->DestroyActor(this);
	}
}

