// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemy001Character.h"

#include "Components/CapsuleComponent.h"
#include "Dmcv2/Dmc/ActionSystem/BaseActionComponent.h"
#include "Dmcv2/Dmc/ActionSystem/Em001Handlers/HitGetUpHandler.h"
#include "Dmcv2/Dmc/ActionSystem/Em001Handlers/HitLandedHandler.h"
#include "Dmcv2/Dmc/ActionSystem/Em001Handlers/HitNormalHandler.h"
#include "Dmcv2/Dmc/ActionSystem/Em001Handlers/HitSilentHandler.h"
#include "Dmcv2/Dmc/ActionSystem/Em001Handlers/HitVectorHandler.h"
#include "Dmcv2/Dmc/Tools/UPrintTool.h"


AEnemy001Character::AEnemy001Character()
{
	// PrimaryActorTick.bCanEverTick = true;
	
}

void AEnemy001Character::BeginPlay()
{
	Super::BeginPlay();
	InitComponent();
	InitializeActionTable();
}

void AEnemy001Character::InitComponent() const
{
	USkeletalMeshComponent* SkeletalMeshComponent = GetMesh();
	
	if (USkeletalMesh* SkeletalMesh = LoadObject<USkeletalMesh>(nullptr, TEXT("SkeletalMesh'/Game/enemy/em001/em001.em001'")))
	{
		SkeletalMeshComponent->SetSkeletalMesh(SkeletalMesh);
		GetCapsuleComponent()->InitCapsuleSize(45.f, 90.0f);
		SkeletalMeshComponent->SetRelativeLocation(FVector(0,0,-90));
		SkeletalMeshComponent->SetRelativeRotation(FRotator(0,-90,0));
	}

	if (UClass* Class = LoadClass<UAnimInstance>(nullptr, TEXT("Blueprint'/Game/MyGame/Enemy/ABP_Em001.ABP_Em001_C'")))
	{
		SkeletalMeshComponent->SetAnimClass(Class);
	}
}

void AEnemy001Character::InitializeActionTable() 
{
	BaseActionComponent->SetupActionTable(TEXT("DataTable'/Game/MyGame/Enemy/DT_Em.DT_Em'"));
	InitializeActionMapping();
}

void AEnemy001Character::InitializeActionMapping() 
{
	UHitNormalHandler* HitNormalHandler = NewObject<UHitNormalHandler>(this);
	HitNormalHandler->Setup(this);
	BaseActionComponent->ActionHandlerMapping.Add(None * 100 + Hit_Normal, HitNormalHandler);

	UHitVectorHandler* HitVectorHandler = NewObject<UHitVectorHandler>(this);
	HitVectorHandler->Setup(this);
	BaseActionComponent->ActionHandlerMapping.Add(None * 100 + Hit_Vector, HitVectorHandler);

	UHitLandedHandler* HitLandedHandler = NewObject<UHitLandedHandler>(this);
	HitLandedHandler->Setup(this);
	BaseActionComponent->ActionHandlerMapping.Add(None * 100 + Hit_Land, HitLandedHandler);

	UHitGetUpHandler* HitGetUpHandler = NewObject<UHitGetUpHandler>(this);
	HitGetUpHandler->Setup(this);
	BaseActionComponent->ActionHandlerMapping.Add(None * 100 + Hit_Getup, HitGetUpHandler);

	UHitSilentHandler* HitSilentHandler = NewObject<UHitSilentHandler>(this);
	HitSilentHandler->Setup(this);
	BaseActionComponent->ActionHandlerMapping.Add(None * 100 + Hit_Silent, HitSilentHandler);

	BaseActionComponent->CurrentHandler = HitNormalHandler;
}

void AEnemy001Character::Damage(ABaseCharacter* SourceCharacter, bool bAttach, const EActionType& HitType,
                                const FVector& HitVector, const float SilentDuration, const float AirTime)
{
	
	if(HitType == EActionType::Hit_Normal)
	{
		UBaseActionHandler* BaseActionHandler = BaseActionComponent->FindActionHandler(EWeaponType::None, EActionType::Hit_Normal);
		UHitNormalHandler* HitNormalHandler = Cast<UHitNormalHandler>(BaseActionHandler);
		HitNormalHandler->SourceCharacter = SourceCharacter;
		HitNormalHandler->AirTime = AirTime;
		HitNormalHandler->Pre_1();
	}else if(HitType == EActionType::Hit_Vector)
	{
		UBaseActionHandler* BaseActionHandler = BaseActionComponent->FindActionHandler(EWeaponType::None, EActionType::Hit_Vector);
		UHitVectorHandler* HitVectorHandler = Cast<UHitVectorHandler>(BaseActionHandler);
		HitVectorHandler->SourceCharacter = SourceCharacter;
		HitVectorHandler->Vector = HitVector;
		HitVectorHandler->Pre_1();
	}else if(HitType == EActionType::Hit_Silent)
	{
		UBaseActionHandler* BaseActionHandler = BaseActionComponent->FindActionHandler(EWeaponType::None, EActionType::Hit_Silent);
		UHitSilentHandler* HitSilentHandler = Cast<UHitSilentHandler>(BaseActionHandler);
		HitSilentHandler->SourceCharacter = SourceCharacter;
		HitSilentHandler->PlayRate = 0.f;
		HitSilentHandler->Duration = SilentDuration;
		HitSilentHandler->Pre_1();
	}
}



void AEnemy001Character::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AEnemy001Character::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

