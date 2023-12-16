// Fill out your copyright notice in the Description page of Project Settings.


#include "ForceEdgeBackFrontHandler.h"

#include "Dmcv2/Dmc/Actor/BladeLightActor.h"
#include "Dmcv2/Dmc/Character/BaseCharacter.h"
#include "Dmcv2/Dmc/Tools/UPrintTool.h"

void UForceEdgeBackFrontHandler::Setup(ABaseCharacter* Character)
{
	Super::Setup(Character);
	ActionComponent->FindAction(HandleAction, EWeaponType::ForceEdge, EActionType::N_Back_Front_Attack);
}

void UForceEdgeBackFrontHandler::Exec()
{
	
	HandleAction.ActionLifeCycle = EActionLifeCycle::Exec;
	
}

void UForceEdgeBackFrontHandler::After_1()
{
	HandleAction.ActionLifeCycle = EActionLifeCycle::After_1;
	UUPrintTool::Info(FString::Printf(TEXT("long press time = %f"), CurrentPressTime));
	if(!bReleased)
	{
		ActionComponent->FindActionHandlerExec(HandleAction.WeaponType, HandleAction.CurrentAnim.SubActionType);
	}
}

void UForceEdgeBackFrontHandler::CommonSignal_1()
{
	if (UClass* Class = LoadClass<AActor>(nullptr, TEXT("Blueprint'/Game/MyGame/Vergil/BP_BladeLight.BP_BladeLight_C'")))
	{
		ABladeLightActor* SpawnActor = GetWorld()->SpawnActor<ABladeLightActor>(Class,SelfCharacter->GetActorTransform());
		FRotator ActorRotation = SelfCharacter->GetActorRotation();
		ActorRotation.Roll += 45;
		SpawnActor->Fire(SelfCharacter, SelfCharacter->FocusCharacter, ActorRotation);
	}
}

void UForceEdgeBackFrontHandler::CommonSignal_2()
{
	if (UClass* Class = LoadClass<AActor>(nullptr, TEXT("Blueprint'/Game/MyGame/Vergil/BP_BladeLight.BP_BladeLight_C'")))
	{
		ABladeLightActor* SpawnActor = GetWorld()->SpawnActor<ABladeLightActor>(Class,SelfCharacter->GetActorTransform());
		FRotator ActorRotation = SelfCharacter->GetActorRotation();
		ActorRotation.Roll -= 45;
		SpawnActor->Fire(SelfCharacter, SelfCharacter->FocusCharacter, ActorRotation);
	}
}

