// Fill out your copyright notice in the Description page of Project Settings.


#include "YamatoExHandler.h"

#include "Components/LightComponent.h"
#include "Dmcv2/Dmc/Character/BaseCharacter.h"
#include "Engine/DirectionalLight.h"
#include "Kismet/GameplayStatics.h"
#include "NiagaraFunctionLibrary.h"

UYamatoExHandler::UYamatoExHandler()
{
	static ConstructorHelpers::FObjectFinder<UNiagaraSystem> NiagaraAsset(TEXT("NiagaraSystem'/Game/FX/ciyuanzhanjue/NS_CYZJ.NS_CYZJ'"));

	if(NiagaraAsset.Succeeded())
	{
		NiagaraSystem = NiagaraAsset.Object;
	}
	
}

void UYamatoExHandler::Setup(ABaseCharacter* Character)
{
	Super::Setup(Character);
	ActionComponent->FindAction(HandleAction, EWeaponType::Yamato, EActionType::N_Ex);
}

void UYamatoExHandler::Pre_1()
{
	Super::Pre_1();
	AActor* ActorLight = UGameplayStatics::GetActorOfClass(GetWorld(), ADirectionalLight::StaticClass());

	const ADirectionalLight* DirectionalLight = Cast<ADirectionalLight>(ActorLight);
	DirectionalLight->GetLightComponent()->SetIntensity(0.5);
}

void UYamatoExHandler::Exec()
{
	HandleAction.ActionLifeCycle = EActionLifeCycle::Exec;
	FRotator ActorRotation = SelfCharacter->GetActorRotation();
	ActorRotation.Yaw += 180;
	SelfCharacter->SetActorRotation(ActorRotation);
	SelfCharacter->SetActorHiddenInGame(true);
	
	GetWorld()->GetTimerManager().SetTimer(EndTimeHandle, this, &UYamatoExHandler::CallEndAnim, 3, false);
	if(SelfCharacter->FocusCharacter && NiagaraSystem)
	{
		UNiagaraFunctionLibrary::SpawnSystemAtLocation(GetWorld(), NiagaraSystem, SelfCharacter->GetActorLocation());
		SelfCharacter->FocusCharacter->Damage(SelfCharacter,false, EActionType::Hit_Silent,FVector::Zero(), 5.f);
	}
}

void UYamatoExHandler::After_1()
{
	HandleAction.ActionLifeCycle = EActionLifeCycle::After_1;
}

void UYamatoExHandler::After_3()
{
	Super::After_3();
	AActor* ActorLight = UGameplayStatics::GetActorOfClass(GetWorld(), ADirectionalLight::StaticClass());
	const ADirectionalLight* DirectionalLight = Cast<ADirectionalLight>(ActorLight);
	DirectionalLight->GetLightComponent()->SetIntensity(3);
	SelfCharacter->FocusCharacter->Damage(SelfCharacter,false,EActionType::Hit_Vector,FVector(0,300,1000));
}

void UYamatoExHandler::CallEndAnim()
{
	SelfCharacter->SetActorHiddenInGame(false);
	HandleAction.CurrentAnim = HandleAction.AnimArray[1];
	HandleAction.Index = 2;
	ActionComponent->bToggleSignal = !ActionComponent->bToggleSignal;
}

