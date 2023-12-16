// Fill out your copyright notice in the Description page of Project Settings.


#include "ForceEdgeBackFrontAfterHandler.h"

#include "Dmcv2/Dmc/Actor/BladeLightActor.h"
#include "Dmcv2/Dmc/Character/BaseCharacter.h"

void UForceEdgeBackFrontAfterHandler::Setup(ABaseCharacter* Character)
{
	Super::Setup(Character);
	ActionComponent->FindAction(HandleAction, EWeaponType::ForceEdge, EActionType::S_ForceEdge_Back_Front_Attack_After);
}

void UForceEdgeBackFrontAfterHandler::Pre_2()
{
	if(!bReleased)
	{
		bCrossPre2 = true;
		HandleAction.Index = 1;
		HandleAction.CurrentAnim = HandleAction.AnimArray[HandleAction.Index];
		ActionComponent->bToggleSignal = !ActionComponent->bToggleSignal;
	}else
	{
		bCrossPre2 = true;
		FinishReleased();
	}
}

void UForceEdgeBackFrontAfterHandler::FinishReleased()
{
	if(bCrossPre2)
	{
		bCrossPre2 = false;
		HandleAction.Index = 2;
		HandleAction.CurrentAnim = HandleAction.AnimArray[HandleAction.Index];
		ActionComponent->bToggleSignal = !ActionComponent->bToggleSignal;
	}
}

void UForceEdgeBackFrontAfterHandler::CommonSignal_1()
{
	if (UClass* Class = LoadClass<AActor>(nullptr, TEXT("Blueprint'/Game/MyGame/Vergil/BP_BladeLight.BP_BladeLight_C'")))
	{
		ABladeLightActor* SpawnActor = GetWorld()->SpawnActor<ABladeLightActor>(Class,SelfCharacter->GetActorTransform());
		const FRotator ActorRotation = SelfCharacter->GetActorRotation();
		SpawnActor->Fire(SelfCharacter, SelfCharacter->FocusCharacter, ActorRotation, 0.2, true);
	}
}
