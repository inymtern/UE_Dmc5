// Fill out your copyright notice in the Description page of Project Settings.


#include "CollisionTraceTool.h"

bool UCollisionTraceTool::BoxOverlapTrace(const UWorld* World, TArray<FOverlapResult>& HitResults, const FVector& Location,  const FVector& Size, const FRotator& Rotation, const bool bIgnoreSelf)
{
	
	FCollisionQueryParams QueryParams;
	if(bIgnoreSelf)
	{
		if (const APlayerController* FirstPlayerController = World->GetFirstPlayerController())
		{
			QueryParams.AddIgnoredActor(FirstPlayerController->GetPawn());
		}
	}
	DrawDebugBox(World, Location, Size, Rotation.Quaternion(), FColor::Red, false, 1.f);
	return World->OverlapMultiByChannel(HitResults, Location, Rotation.Quaternion(), ECollisionChannel::ECC_Pawn, FCollisionShape::MakeBox(Size), QueryParams);
}
