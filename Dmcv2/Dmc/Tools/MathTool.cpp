// Fill out your copyright notice in the Description page of Project Settings.


#include "MathTool.h"

#include "Dmcv2/Dmc/Anim/Notify/Offset.h"

ECustomDir UMathTool::CalcRefDirection(const FVector& SelfForward, const FVector& SelfLocation, const FVector& TargetLocation)
{
	const double DotProduct = FVector::DotProduct(TargetLocation - SelfLocation, SelfForward);

	if(DotProduct > 0.5) return ECustomDir::D_Front;
	return ECustomDir::D_Back;
}
