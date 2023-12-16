// Fill out your copyright notice in the Description page of Project Settings.


#include "VergilCharacter.h"

#include "EditorDirectories.h"
#include "Enemy001Character.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Dmcv2/Dmc/ActionSystem/BaseActionComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "NiagaraComponent.h"
#include "NiagaraSystem.h"
#include "Dmcv2/Dmc/ActionSystem/Handlers/BaseActionHandler.h"
#include "Dmcv2/Dmc/ActionSystem/Handlers/FallToLanded.h"
#include "Dmcv2/Dmc/ActionSystem/Handlers/LongPressAutoTriggerHandler.h"
#include "Dmcv2/Dmc/ActionSystem/Handlers/Beowulf/BeowulfAirComboHandler.h"
#include "Dmcv2/Dmc/ActionSystem/Handlers/Beowulf/BeowulfBackFrontHandler.h"
#include "Dmcv2/Dmc/ActionSystem/Handlers/Beowulf/BeowulfBackHandler.h"
#include "Dmcv2/Dmc/ActionSystem/Handlers/Beowulf/BeowulfFrontHandler.h"
#include "Dmcv2/Dmc/ActionSystem/Handlers/Common/DeFlashHandler.h"
#include "Dmcv2/Dmc/ActionSystem/Handlers/Common/FlashHandler.h"
#include "Dmcv2/Dmc/ActionSystem/Handlers/Common/FlashWhenAttackHandler.h"
#include "Dmcv2/Dmc/ActionSystem/Handlers/Common/JumpHandler.h"
#include "Dmcv2/Dmc/ActionSystem/Handlers/Common/LandedHandler.h"
#include "Dmcv2/Dmc/ActionSystem/Handlers/Common/TauntHandler.h"
#include "Dmcv2/Dmc/ActionSystem/Handlers/ForceEdge/ForceEdgeAirBackHandler.h"
#include "Dmcv2/Dmc/ActionSystem/Handlers/ForceEdge/ForceEdgeAirComboHandler.h"
#include "Dmcv2/Dmc/ActionSystem/Handlers/ForceEdge/ForceEdgeAirFrontHandler.h"
#include "Dmcv2/Dmc/ActionSystem/Handlers/ForceEdge/ForceEdgeBackFrontAfterHandler.h"
#include "Dmcv2/Dmc/ActionSystem/Handlers/ForceEdge/ForceEdgeBackFrontHandler.h"
#include "Dmcv2/Dmc/ActionSystem/Handlers/ForceEdge/ForceEdgeBackHandler.h"
#include "Dmcv2/Dmc/ActionSystem/Handlers/ForceEdge/ForceEdgeComboA1Handler.h"
#include "Dmcv2/Dmc/ActionSystem/Handlers/ForceEdge/ForceEdgeComboA2Handler.h"
#include "Dmcv2/Dmc/ActionSystem/Handlers/ForceEdge/ForceEdgeComboA3Handler.h"
#include "Dmcv2/Dmc/ActionSystem/Handlers/ForceEdge/ForceEdgeComboAHandler.h"
#include "Dmcv2/Dmc/ActionSystem/Handlers/ForceEdge/ForceEdgeFrontAttackAfterHandler.h"
#include "Dmcv2/Dmc/ActionSystem/Handlers/ForceEdge/ForceEdgeFrontHandler.h"
#include "Dmcv2/Dmc/ActionSystem/Handlers/Yamato/YamatoAirBackHandler.h"
#include "Dmcv2/Dmc/ActionSystem/Handlers/Yamato/YamatoAirComboA1Handler.h"
#include "Dmcv2/Dmc/ActionSystem/Handlers/Yamato/YamatoAirComboAHandler.h"
#include "Dmcv2/Dmc/ActionSystem/Handlers/Yamato/YamatoBackFrontAttackHandler.h"
#include "Dmcv2/Dmc/ActionSystem/Handlers/Yamato/YamatoBackHandler.h"
#include "Dmcv2/Dmc/ActionSystem/Handlers/Yamato/YamatoCiYuanZhanHandler.h"
#include "Dmcv2/Dmc/ActionSystem/Handlers/Yamato/YamatoComboA1Handler.h"
#include "Dmcv2/Dmc/ActionSystem/Handlers/Yamato/YamatoComboA2Handler.h"
#include "Dmcv2/Dmc/ActionSystem/Handlers/Yamato/YamatoComboAHandler.h"
#include "Dmcv2/Dmc/ActionSystem/Handlers/Yamato/YamatoExHandler.h"
#include "Dmcv2/Dmc/ActionSystem/Handlers/Yamato/YamatoFrontHandler.h"
#include "Dmcv2/Dmc/Actor/GhostSwordActor.h"
#include "Dmcv2/Dmc/Tools/CollisionTraceTool.h"
#include "Dmcv2/Dmc/Tools/UPrintTool.h"
#include "Kismet/GameplayStatics.h"

AVergilCharacter::AVergilCharacter()
{
	// PrimaryActorTick.bCanEverTick = true;
	InitializeMeshComponent();
	InitializeCamera();
	InitCharacterSetting();
}

void AVergilCharacter::BeginPlay()
{
	Super::BeginPlay();
	InitializeInput();
	InitializeMeshSetting();
	InitializeAnimBlueprintSetting();
	InitializeWeaponSetting();
	InitializeActionTable();
}

void AVergilCharacter::InitCharacterSetting()
{

	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;
	
	GetCharacterMovement()->bOrientRotationToMovement = true; 
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 500.0f, 0.0f); 

	GetCharacterMovement()->JumpZVelocity = 700.f;
	GetCharacterMovement()->AirControl = 0.35f;
	GetCharacterMovement()->MaxWalkSpeed = 500.f;
	GetCharacterMovement()->MinAnalogWalkSpeed = 20.f;
	GetCharacterMovement()->BrakingDecelerationWalking = 2000.f;
	GetCharacterMovement()->BrakingDecelerationFalling = 1500.0f;
}

void AVergilCharacter::InitializeInput() const
{
	if (const APlayerController* PlayerController = Cast<APlayerController>(Controller))
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			Subsystem->AddMappingContext(DefaultMappingContext, 0);
		}
	}
}

void AVergilCharacter::InitializeMeshComponent()
{
	USkeletalMeshComponent* SkeletalMeshComponent = GetMesh();
	if (USkeletalMesh* SkeletalMesh = LoadObject<USkeletalMesh>(nullptr, TEXT("SkeletalMesh'/Game/Vergil_New/Mesh/body/vergil_body.vergil_body'")))
	{
		SkeletalMeshComponent->SetSkeletalMesh(SkeletalMesh);
	}

	HeadMeshComponent = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("HeadMeshComponent"));
	if (USkeletalMesh* SkeletalMesh = LoadObject<USkeletalMesh>(nullptr, TEXT("SkeletalMesh'/Game/Vergil_New/Mesh/Head/vergil_head.vergil_head'")))
	{
		HeadMeshComponent->SetSkeletalMesh(SkeletalMesh);
	}

	HairMeshComponent = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("HairMeshComponent"));
	if (USkeletalMesh* SkeletalMesh = LoadObject<USkeletalMesh>(nullptr, TEXT("SkeletalMesh'/Game/Vergil_New/Mesh/Hair/vergil_hair.vergil_hair'")))
	{
		HairMeshComponent->SetSkeletalMesh(SkeletalMesh);
	}

	YamatoFullComponent = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("YamatoFullComponent"));
	if (USkeletalMesh* SkeletalMesh = LoadObject<USkeletalMesh>(nullptr, TEXT("SkeletalMesh'/Game/Vergil_New/Mesh/Yamato_Full/yamato_full.yamato_full'")))
	{
		YamatoFullComponent->SetSkeletalMesh(SkeletalMesh);
	}

	YamatoBladeComponent = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("YamatoBladeComponent"));
	if (USkeletalMesh* SkeletalMesh = LoadObject<USkeletalMesh>(nullptr, TEXT("SkeletalMesh'/Game/Vergil_New/Mesh/Yamato_Blade/yamato_blade.yamato_blade'")))
	{
		YamatoBladeComponent->SetSkeletalMesh(SkeletalMesh);
	}

	YamatoScabComponent = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("YamatoScabComponent"));
	if (USkeletalMesh* SkeletalMesh = LoadObject<USkeletalMesh>(nullptr, TEXT("SkeletalMesh'/Game/Vergil_New/Mesh/Yamato_Scab/yamato_scab.yamato_scab'")))
	{
		YamatoBladeComponent->SetSkeletalMesh(SkeletalMesh);
	}

	ForceEdgeComponent = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("ForceEdgeComponent"));
	if (USkeletalMesh* SkeletalMesh = LoadObject<USkeletalMesh>(nullptr, TEXT("SkeletalMesh'/Game/Vergil_New/Mesh/ForceBlade/forceblade2.forceblade2'")))
	{
		ForceEdgeComponent->SetSkeletalMesh(SkeletalMesh);
	}
	
	BeowulfMeshComponent_Hand_L = CreateDefaultSubobject<UNiagaraComponent>(TEXT("BeowulfMeshComponent_Hand_L"));
	BeowulfMeshComponent_Hand_R = CreateDefaultSubobject<UNiagaraComponent>(TEXT("BeowulfMeshComponent_Hand_R"));
	BeowulfMeshComponent_Foot_L = CreateDefaultSubobject<UNiagaraComponent>(TEXT("BeowulfMeshComponent_Foot_L"));
	BeowulfMeshComponent_Foot_R = CreateDefaultSubobject<UNiagaraComponent>(TEXT("BeowulfMeshComponent_Foot_R"));


	// static ConstructorHelpers::FObjectFinder<UNiagaraSystem> BeowulfNiagara(TEXT("NiagaraSystem'/Game/FX/ciyuanzhan/NS_Slash_Small.NS_Slash_Small'"));
	//
	// if(BeowulfNiagara.Succeeded())
	// {
	// 	BeowulfMeshComponent_Hand_L->SetAsset(BeowulfNiagara.Object);
	// 	BeowulfMeshComponent_Hand_R->SetAsset(BeowulfNiagara.Object);
	// 	BeowulfMeshComponent_Foot_L->SetAsset(BeowulfNiagara.Object);
	// 	BeowulfMeshComponent_Foot_R->SetAsset(BeowulfNiagara.Object);
	// }

	GetCapsuleComponent()->InitCapsuleSize(32.f, 90.0f);
	
	SkeletalMeshComponent->SetRelativeLocation(FVector(0,0,-90));
	SkeletalMeshComponent->SetRelativeRotation(FRotator(0,-90,0));
	
}

void AVergilCharacter::InitializeMeshSetting() const
{
	HeadMeshComponent->AttachToComponent(GetMesh(),FAttachmentTransformRules::SnapToTargetIncludingScale, FName("HeadSocket"));
	HairMeshComponent->AttachToComponent(GetMesh(),FAttachmentTransformRules::SnapToTargetIncludingScale, FName("HeadSocket"));

	YamatoBladeComponent->AttachToComponent(GetMesh(),FAttachmentTransformRules::SnapToTargetIncludingScale, FName("Weapon_R"));
	YamatoScabComponent->AttachToComponent(GetMesh(),FAttachmentTransformRules::SnapToTargetIncludingScale, FName("Weapon_L"));
	YamatoFullComponent->AttachToComponent(GetMesh(),FAttachmentTransformRules::SnapToTargetIncludingScale, FName("Weapon_L"));

	ForceEdgeComponent->AttachToComponent(GetMesh(),FAttachmentTransformRules::SnapToTargetNotIncludingScale, FName("BackWeaponSocket"));
	
	BeowulfMeshComponent_Hand_L->AttachToComponent(GetMesh(),FAttachmentTransformRules::SnapToTargetIncludingScale, FName("L_HandSocket"));
	BeowulfMeshComponent_Hand_R->AttachToComponent(GetMesh(),FAttachmentTransformRules::SnapToTargetIncludingScale, FName("R_HandSocket"));
	BeowulfMeshComponent_Foot_R->AttachToComponent(GetMesh(),FAttachmentTransformRules::SnapToTargetIncludingScale, FName("L_FootSocket"));
	BeowulfMeshComponent_Foot_L->AttachToComponent(GetMesh(),FAttachmentTransformRules::SnapToTargetIncludingScale, FName("R_FootSocket"));

	YamatoBladeComponent->SetVisibility(false);
	YamatoScabComponent->SetVisibility(false);
	YamatoFullComponent->SetVisibility(true);
}

void AVergilCharacter::InitializeCamera()
{
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->TargetArmLength = CameraDefaultDistance;
	CameraBoom->bUsePawnControlRotation = true;
	CameraBoom->bEnableCameraLag = true;
	CameraBoom->CameraLagSpeed = 4.f;
	CameraBoom->CameraLagMaxDistance = 180.f;
	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName); 
	FollowCamera->bUsePawnControlRotation = false;
	CameraBoom->bDoCollisionTest = false;
}

void AVergilCharacter::InitializeActionTable() 
{
	BaseActionComponent->SetupActionTable(TEXT("DataTable'/Game/MyGame/Vergil/DT_Vergil.DT_Vergil'"));
	InitializeActionMapping();
}

void AVergilCharacter::InitializeActionMapping() 
{
	if(BaseActionComponent->ActionMapping.IsEmpty()) return;

	UYamatoBackFrontAttackHandler* YamatoBackAttackHandler = NewObject<UYamatoBackFrontAttackHandler>(this);
	YamatoBackAttackHandler->Setup(this);
	BaseActionComponent->ActionHandlerMapping.Add(Yamato * 100 + N_Back_Front_Attack, YamatoBackAttackHandler);

	UYamatoComboAHandler* YamatoComboAHandler = NewObject<UYamatoComboAHandler>(this);
	YamatoComboAHandler->Setup(this);
	BaseActionComponent->ActionHandlerMapping.Add(Yamato * 100 + N_Combo_A, YamatoComboAHandler);

	UYamatoComboA1Handler* YamatoComboA1Handler = NewObject<UYamatoComboA1Handler>(this);
	YamatoComboA1Handler->Setup(this);
	BaseActionComponent->ActionHandlerMapping.Add(Yamato * 100 + N_Combo_A1, YamatoComboA1Handler);

	UForceEdgeComboAHandler* ForceEdgeComboAHandler = NewObject<UForceEdgeComboAHandler>(this);
	ForceEdgeComboAHandler->Setup(this);
	BaseActionComponent->ActionHandlerMapping.Add(ForceEdge * 100 + N_Combo_A, ForceEdgeComboAHandler);

	UYamatoComboA2Handler* YamatoComboA2Handler = NewObject<UYamatoComboA2Handler>(this);
	YamatoComboA2Handler->Setup(this);
	BaseActionComponent->ActionHandlerMapping.Add(Yamato * 100 + N_Combo_A2, YamatoComboA2Handler);

	UForceEdgeComboA1Handler* ForceEdgeComboA1Handler = NewObject<UForceEdgeComboA1Handler>(this);
	ForceEdgeComboA1Handler->Setup(this);
	BaseActionComponent->ActionHandlerMapping.Add(ForceEdge * 100 + N_Combo_A1, ForceEdgeComboA1Handler);

	UForceEdgeComboA2Handler* ForceEdgeComboA2Handler = NewObject<UForceEdgeComboA2Handler>(this);
	ForceEdgeComboA2Handler->Setup(this);
	BaseActionComponent->ActionHandlerMapping.Add(ForceEdge * 100 + N_Combo_A2, ForceEdgeComboA2Handler);

	UForceEdgeComboA3Handler* ForceEdgeComboA3Handler = NewObject<UForceEdgeComboA3Handler>(this);
	ForceEdgeComboA3Handler->Setup(this);
	BaseActionComponent->ActionHandlerMapping.Add(ForceEdge * 100 + N_Combo_A3, ForceEdgeComboA3Handler);

	UYamatoBackHandler* YamatoBackHandler = NewObject<UYamatoBackHandler>(this);
	YamatoBackHandler->Setup(this);
	BaseActionComponent->ActionHandlerMapping.Add(Yamato * 100 + N_Back_Attack, YamatoBackHandler);

	ULandedHandler* LandedHandler = NewObject<ULandedHandler>(this);
	LandedHandler->Setup(this);
	BaseActionComponent->ActionHandlerMapping.Add(None * 100 + EActionType::Landed, LandedHandler);

	UYamatoAirComboAHandler* YamatoAirComboAHandler = NewObject<UYamatoAirComboAHandler>(this);
	YamatoAirComboAHandler->Setup(this);
	BaseActionComponent->ActionHandlerMapping.Add(Yamato * 100 + N_Air_Combo_A, YamatoAirComboAHandler);

	UYamatoAirComboA1Handler* YamatoAirComboA1Handler = NewObject<UYamatoAirComboA1Handler>(this);
	YamatoAirComboA1Handler->Setup(this);
	BaseActionComponent->ActionHandlerMapping.Add(Yamato * 100 + N_Air_Combo_A1, YamatoAirComboA1Handler);

	UYamatoFrontHandler* YamatoFrontHandler = NewObject<UYamatoFrontHandler>(this);
	YamatoFrontHandler->Setup(this);
	BaseActionComponent->ActionHandlerMapping.Add(Yamato * 100 + N_Front_Attack, YamatoFrontHandler);


	UYamatoAirBackHandler* YamatoAirBackHandler = NewObject<UYamatoAirBackHandler>(this);
	YamatoAirBackHandler->Setup(this);
	BaseActionComponent->ActionHandlerMapping.Add(Yamato * 100 + N_Air_Back_Attack, YamatoAirBackHandler);

	UYamatoExHandler* YamatoExHandler = NewObject<UYamatoExHandler>(this);
	YamatoExHandler->Setup(this);
	BaseActionComponent->ActionHandlerMapping.Add(Yamato * 100 + N_Ex, YamatoExHandler);

	UTauntHandler* TauntHandler = NewObject<UTauntHandler>(this);
	TauntHandler->Setup(this);
	BaseActionComponent->ActionHandlerMapping.Add(None * 100 + N_Taunt, TauntHandler);


	UJumpHandler* JumpHandler = NewObject<UJumpHandler>(this);
	JumpHandler->Setup(this);
	BaseActionComponent->ActionHandlerMapping.Add(None * 100 + EActionType::Jump, JumpHandler);

	UFlashHandler* FlashHandler = NewObject<UFlashHandler>(this);
	FlashHandler->Setup(this);
	BaseActionComponent->ActionHandlerMapping.Add(None * 100 + EActionType::Flash, FlashHandler);

	UDeFlashHandler* DeFlashHandler = NewObject<UDeFlashHandler>(this);
	DeFlashHandler->Setup(this);
	BaseActionComponent->ActionHandlerMapping.Add(None * 100 + EActionType::De_Flash, DeFlashHandler);

	
	UFlashWhenAttackHandler* FlashWhenAttackHandler = NewObject<UFlashWhenAttackHandler>(this);
	FlashWhenAttackHandler->Setup(this);
	BaseActionComponent->ActionHandlerMapping.Add(None * 100 + EActionType::Attack_Flash, FlashWhenAttackHandler);

	UForceEdgeBackHandler* ForceEdgeBackHandler = NewObject<UForceEdgeBackHandler>(this);
	ForceEdgeBackHandler->Setup(this);
	BaseActionComponent->ActionHandlerMapping.Add(ForceEdge * 100 + EActionType::N_Back_Attack, ForceEdgeBackHandler);

	UForceEdgeAirBackHandler* ForceEdgeAirBackHandler = NewObject<UForceEdgeAirBackHandler>(this);
	ForceEdgeAirBackHandler->Setup(this);
	BaseActionComponent->ActionHandlerMapping.Add(ForceEdge * 100 + EActionType::N_Air_Back_Attack, ForceEdgeAirBackHandler);

	UYamatoCiYuanZhanHandler* YamatoCiYuanZhanHandler = NewObject<UYamatoCiYuanZhanHandler>(this);
	YamatoCiYuanZhanHandler->Setup(this);
	BaseActionComponent->ActionHandlerMapping.Add(Yamato * 100 + EActionType::N_Long_Press, YamatoCiYuanZhanHandler);

	UForceEdgeAirComboHandler* ForceEdgeAirComboHandler = NewObject<UForceEdgeAirComboHandler>(this);
	ForceEdgeAirComboHandler->Setup(this);
	BaseActionComponent->ActionHandlerMapping.Add(ForceEdge * 100 + EActionType::N_Air_Combo_A, ForceEdgeAirComboHandler);

	UForceEdgeFrontHandler* ForceEdgeFrontHandler = NewObject<UForceEdgeFrontHandler>(this);
	ForceEdgeFrontHandler->Setup(this);
	BaseActionComponent->ActionHandlerMapping.Add(ForceEdge * 100 + EActionType::N_Front_Attack, ForceEdgeFrontHandler);

	UForceEdgeFrontAttackAfterHandler* ForceEdgeFrontAttackAfterHandler = NewObject<UForceEdgeFrontAttackAfterHandler>(this);
	ForceEdgeFrontAttackAfterHandler->Setup(this);
	BaseActionComponent->ActionHandlerMapping.Add(ForceEdge * 100 + EActionType::S_ForceEdge_Front_Attack_After, ForceEdgeFrontAttackAfterHandler);

	UForceEdgeAirFrontHandler* ForceEdgeAirFrontHandler = NewObject<UForceEdgeAirFrontHandler>(this);
	ForceEdgeAirFrontHandler->Setup(this);
	BaseActionComponent->ActionHandlerMapping.Add(ForceEdge * 100 + EActionType::N_Air_Front_Attack, ForceEdgeAirFrontHandler);


	UBeowulfBackHandler* BeowulfBackHandler = NewObject<UBeowulfBackHandler>(this);
	BeowulfBackHandler->Setup(this);
	BaseActionComponent->ActionHandlerMapping.Add(Beowulf * 100 + EActionType::N_Back_Attack, BeowulfBackHandler);

	UBeowulfFrontHandler* BeowulfFrontHandler = NewObject<UBeowulfFrontHandler>(this);
	BeowulfFrontHandler->Setup(this);
	BaseActionComponent->ActionHandlerMapping.Add(Beowulf * 100 + EActionType::N_Front_Attack, BeowulfFrontHandler);
	
	UBeowulfBackFrontHandler* BeowulfBackFrontHandler = NewObject<UBeowulfBackFrontHandler>(this);
	BeowulfBackFrontHandler->Setup(this);
	BaseActionComponent->ActionHandlerMapping.Add(Beowulf * 100 + EActionType::N_Back_Front_Attack, BeowulfBackFrontHandler);


	UBeowulfAirComboHandler* BeowulfAirComboHandler = NewObject<UBeowulfAirComboHandler>(this);
	BeowulfAirComboHandler->Setup(this);
	BaseActionComponent->ActionHandlerMapping.Add(Beowulf * 100 + EActionType::N_Air_Combo_A, BeowulfAirComboHandler);

	UForceEdgeBackFrontHandler* ForceEdgeBackFrontHandler = NewObject<UForceEdgeBackFrontHandler>(this);
	ForceEdgeBackFrontHandler->Setup(this);
	BaseActionComponent->ActionHandlerMapping.Add(ForceEdge * 100 + EActionType::N_Back_Front_Attack, ForceEdgeBackFrontHandler);

	UForceEdgeBackFrontAfterHandler* ForceEdgeBackFrontAfterHandler = NewObject<UForceEdgeBackFrontAfterHandler>(this);
	ForceEdgeBackFrontAfterHandler->Setup(this);
	BaseActionComponent->ActionHandlerMapping.Add(ForceEdge * 100 + EActionType::S_ForceEdge_Back_Front_Attack_After, ForceEdgeBackFrontAfterHandler);

	BaseActionComponent->CurrentHandler = YamatoBackAttackHandler;
}

void AVergilCharacter::InitializeWeaponSetting()
{
	FWeaponInfo Yamato;
	Yamato.Path = TEXT("Blueprint'/Game/MyGame/Vergil/ABP_Yamato.ABP_Yamato_C'");
	Yamato.Weapon = EWeaponType::Yamato;
	Yamato.AnimClass = LoadClass<UAnimInstance>(nullptr, *Yamato.Path);
	 

	FWeaponInfo Beowulf;
	Beowulf.Path = TEXT("Blueprint'/Game/MyGame/Vergil/ABP_Beowulf.ABP_Beowulf_C'");
	Beowulf.Weapon = EWeaponType::Beowulf;
	Beowulf.AnimClass = LoadClass<UAnimInstance>(nullptr, *Beowulf.Path);
	
	FWeaponInfo ForceBlade;
	ForceBlade.Path = TEXT("Blueprint'/Game/MyGame/Vergil/ABP_ForceEdge.ABP_ForceEdge_C'");
	ForceBlade.Weapon = EWeaponType::ForceEdge;
	ForceBlade.AnimClass = LoadClass<UAnimInstance>(nullptr, *ForceBlade.Path);
	
	WeaponInfos.Add(Yamato);
	WeaponInfos.Add(Beowulf);
	WeaponInfos.Add(ForceBlade);

	CurrentWeaponIndex = 0;
	
	GetMesh()->LinkAnimClassLayers(Yamato.AnimClass);

	ShowWeapon();
}

void AVergilCharacter::InitializeAnimBlueprintSetting() const
{
	UClass* BaseAbpClass = LoadClass<UAnimInstance>(nullptr, TEXT("Blueprint'/Game/MyGame/Vergil/ABP_Vergil_Base.ABP_Vergil_Base_C'"));
	GetMesh()->SetAnimClass(BaseAbpClass);
}






void AVergilCharacter::MoveStart(const FInputActionValue& Value)
{
	MoveAxisValue = Value.Get<FVector2D>();
}

void AVergilCharacter::MoveTriggered(const FInputActionValue& Value)
{
	MoveAxisValue = Value.Get<FVector2D>();
	if(bFocusMode)
	{
		FRotator ControlRotation = GetControlRotation();
		ControlRotation.Pitch = 0;
		const FVector ControllerForwardVector = ControlRotation.Vector();
		const double DotForward = FVector::DotProduct(GetActorForwardVector().GetSafeNormal(), ControllerForwardVector.GetSafeNormal());
		const double DotRight = FVector::DotProduct(GetActorRightVector().GetSafeNormal(), ControllerForwardVector.GetSafeNormal()); // 1在左 -1在右
		BackFrontRecord(DotForward, DotRight);
	}else
	{
		const FVector DirectionVector = CalcDirectionVector();
		CurrentMoveDirection = CalcDirection(DirectionVector, GetActorRotation());
		SetActorDeltaRotator(CurrentMoveDirection);
	}
}

void AVergilCharacter::MoveCompleted(const FInputActionValue& Value)
{
	MoveAxisValue = FVector2D::Zero();
	auto ResetInputCallBack = [this]()
	{
		
		LastInputDirection = EInputDirection::Nil;
	};
	GetWorld()->GetTimerManager().SetTimer(InputResetTimerHandle, ResetInputCallBack, ResetDelayTime, false);
}

void AVergilCharacter::LookStart(const FInputActionValue& Value)
{
	bIsMovingCamera = true;
}

void AVergilCharacter::LookTriggered(const FInputActionValue& Value)
{
	const FVector2D LookAxisVector = Value.Get<FVector2D>();
	if (Controller != nullptr)
	{
		AddControllerYawInput(LookAxisVector.X * YawSpeed);
		AddControllerPitchInput(LookAxisVector.Y * PitchSpeed);
		FRotator ControlRotation = GetControlRotation();
		if(ControlRotation.Pitch < 180)
		{
			ControlRotation.Pitch += 360;
		}
		ControlRotation.Pitch = FMath::Clamp(ControlRotation.Pitch, MinPitchAngle, MaxPitchAngle);
		GetController()->SetControlRotation(ControlRotation);
	}
}

void AVergilCharacter::LookCompleted(const FInputActionValue& Value)
{
	bIsMovingCamera = false;
}

void AVergilCharacter::LeftMouseStart()
{
	const bool bIsFalling = GetCharacterMovement()->IsFalling();
	
	if(LastInputDirection == EInputDirection::BackFront)
	{
		BaseActionComponent->FindActionHandlerExec(WeaponInfos[CurrentWeaponIndex].Weapon, bIsFalling ? N_Air_Back_Front_Attack : N_Back_Front_Attack);
	}else if(LastInputDirection == EInputDirection::Front)
	{
		BaseActionComponent->FindActionHandlerExec(WeaponInfos[CurrentWeaponIndex].Weapon, bIsFalling ? N_Air_Front_Attack : N_Front_Attack);
	}else if(LastInputDirection == EInputDirection::Back)
	{
		BaseActionComponent->FindActionHandlerExec(WeaponInfos[CurrentWeaponIndex].Weapon, bIsFalling ? N_Air_Back_Attack : N_Back_Attack);
	}else
	{
		BaseActionComponent->FindActionHandlerExec(WeaponInfos[CurrentWeaponIndex].Weapon, bIsFalling ? N_Air_Combo_A : N_Combo_A);
	}
}

void AVergilCharacter::LeftMouseTriggered()
{
	// UUPrintTool::Warn(FString::Printf(TEXT("long press is %f"), CurrentLongPressTime));
	// 松开时
	if(WeaponInfos[CurrentWeaponIndex].Weapon == EWeaponType::Yamato)
	{
		if(CurrentLongPressTime > CiYuanZhanThreshold)
		{
			UBaseActionHandler* BaseActionHandler = BaseActionComponent->FindActionHandler(EWeaponType::Yamato, EActionType::N_Long_Press);
			UYamatoCiYuanZhanHandler* YamatoCiYuanZhanHandler = Cast<UYamatoCiYuanZhanHandler>(BaseActionHandler);
			YamatoCiYuanZhanHandler->bIsPerfect = CurrentLongPressTime <= PerfectCiYuanZhanThreshold;
			YamatoCiYuanZhanHandler->Pre_1();
		}
	}else if(WeaponInfos[CurrentWeaponIndex].Weapon == EWeaponType::Beowulf)
	{
		if (ULongPressTriggerHandler* LongPressTriggerHandler = Cast<ULongPressTriggerHandler>(BaseActionComponent->CurrentHandler))
		{
			LongPressTriggerHandler->FinishReleased();
		}
	}else if(WeaponInfos[CurrentWeaponIndex].Weapon == EWeaponType::ForceEdge)
	{
		if (ULongPressTriggerHandler* LongPressTriggerHandler = Cast<ULongPressTriggerHandler>(BaseActionComponent->CurrentHandler))
		{
			LongPressTriggerHandler->FinishReleased();
		}
	}
	
}

void AVergilCharacter::LeftMouseOnGoing()
{
	if(BaseActionComponent->CurrentHandler->HandleAction.ActionLifeCycle < EActionLifeCycle::After_1)
	{
		if (ULongPressAutoTriggerHandler* LongPressAutoTriggerHandler = Cast<ULongPressAutoTriggerHandler>(BaseActionComponent->CurrentHandler))
		{
			LongPressAutoTriggerHandler->CurrentPressTime += GetWorld()->DeltaTimeSeconds;
		}
	}
	CurrentLongPressTime += GetWorld()->DeltaTimeSeconds;
	
	
}

void AVergilCharacter::LeftMouseCompleted()
{
	if(BaseActionComponent->CurrentHandler->HandleAction.ActionLifeCycle < EActionLifeCycle::After_1)
	{
		if (ULongPressAutoTriggerHandler* LongPressAutoTriggerHandler = Cast<ULongPressAutoTriggerHandler>(BaseActionComponent->CurrentHandler))
		{
			LongPressAutoTriggerHandler->bReleased = true;
		}
	}
	CurrentLongPressTime = 0;
}

void AVergilCharacter::RightMouseStart()
{
	if(LastInputDirection == EInputDirection::BackFront)
	{
		GhostSword_BackFront();
	}else if(LastInputDirection == EInputDirection::Front)
	{
		GhostSword_Front();
	}else if(LastInputDirection == EInputDirection::Back)
	{
		GhostSword_Back();
	}else
	{
		GhostSword_Normal();
	}
}

void AVergilCharacter::RightMouseTriggered()
{
}

void AVergilCharacter::RightMouseOnGoing()
{
}

void AVergilCharacter::RightMouseCompleted()
{
}

void AVergilCharacter::GhostSword_BackFront()
{
	if(FocusCharacter)
	{
		const FVector ActorLocation = FocusCharacter->GetActorLocation();
		SpawnGhostSwordInVerticalCircleArea(ActorLocation, 300, 450, 80);
	}
}

void AVergilCharacter::GhostSword_Back()
{
	if(!FocusCharacter) return;
	const FVector ActorLocation = FocusCharacter->GetActorLocation();
	const FVector LocationF = FocusCharacter->GetLocation(MyPlace::F);
	
	AGhostSwordActor* GhostSwordActor1 = GetWorld()->SpawnActor<AGhostSwordActor>(LocationF, (ActorLocation - LocationF).Rotation());
	
	const FVector LocationB = FocusCharacter->GetLocation(MyPlace::B);
	AGhostSwordActor* GhostSwordActor2 = GetWorld()->SpawnActor<AGhostSwordActor>(LocationB, (ActorLocation - LocationB).Rotation());
	
	const FVector LocationR = FocusCharacter->GetLocation(MyPlace::R);
	AGhostSwordActor* GhostSwordActor3 = GetWorld()->SpawnActor<AGhostSwordActor>(LocationR, (ActorLocation - LocationR).Rotation());
	
	const FVector LocationL = FocusCharacter->GetLocation(MyPlace::R);
	AGhostSwordActor* GhostSwordActor6 = GetWorld()->SpawnActor<AGhostSwordActor>(LocationL, (ActorLocation - LocationL).Rotation());
	
	const FVector LocationFL = FocusCharacter->GetLocation(MyPlace::FL);
	AGhostSwordActor* GhostSwordActor7 = GetWorld()->SpawnActor<AGhostSwordActor>(LocationFL, (ActorLocation - LocationFL).Rotation());
	
	const FVector LocationFR = FocusCharacter->GetLocation(MyPlace::FR);
	AGhostSwordActor* GhostSwordActor8 = GetWorld()->SpawnActor<AGhostSwordActor>(LocationFR, (ActorLocation - LocationFR).Rotation());
	
	const FVector LocationBR = FocusCharacter->GetLocation(MyPlace::BR);
	AGhostSwordActor* GhostSwordActor4 = GetWorld()->SpawnActor<AGhostSwordActor>(LocationBR, (ActorLocation - LocationBR).Rotation());
	
	const FVector LocationBL = FocusCharacter->GetLocation(MyPlace::BL);
	AGhostSwordActor* GhostSwordActor5 = GetWorld()->SpawnActor<AGhostSwordActor>(LocationBL, (ActorLocation - LocationBL).Rotation());

	GhostSwordActor1->Fire(true, false, this, FocusCharacter, false,Hit_Vector);
	GhostSwordActor2->Fire(true, false, this, FocusCharacter, false,Hit_Vector);
	GhostSwordActor3->Fire(true, false, this, FocusCharacter, false,Hit_Vector);
	GhostSwordActor6->Fire(true, false, this, FocusCharacter, false,Hit_Vector);
	GhostSwordActor7->Fire(true, false, this, FocusCharacter, false,Hit_Vector);
	GhostSwordActor8->Fire(true, false, this, FocusCharacter, false,Hit_Vector);
	GhostSwordActor4->Fire(true, false, this, FocusCharacter, false,Hit_Vector);
	GhostSwordActor5->Fire(true, false, this, FocusCharacter, true,Hit_Vector);
}

void AVergilCharacter::GhostSword_Front()
{
	FRotator FaceTo = GetActorRotation();
	if(FocusCharacter)
	{
		const FVector ActorLocation = FocusCharacter->GetActorLocation();
		FaceTo = (ActorLocation - GetActorLocation()).Rotation();
	}

	const FVector Vector = FVector(0.4f, 0.4f, 1);
	
	AGhostSwordActor* GhostSwordActor1 = GetWorld()->SpawnActor<AGhostSwordActor>(GetRandomPosition(2), FaceTo);
	GhostSwordActor1->Fire(true, true, this, FocusCharacter, true, EActionType::Hit_Normal, Vector);

	AGhostSwordActor* GhostSwordActor2 = GetWorld()->SpawnActor<AGhostSwordActor>(GetRandomPosition(3), FaceTo);
	GhostSwordActor2->Fire(true, true, this, FocusCharacter, true,Hit_Normal, Vector);

	AGhostSwordActor* GhostSwordActor3 = GetWorld()->SpawnActor<AGhostSwordActor>(GetRandomPosition(4), FaceTo);
	GhostSwordActor3->Fire(true, true, this, FocusCharacter, true,Hit_Normal, Vector);

	AGhostSwordActor* GhostSwordActor6 = GetWorld()->SpawnActor<AGhostSwordActor>(GetRandomPosition(5), FaceTo);
	GhostSwordActor6->Fire(true, true, this, FocusCharacter, true,Hit_Normal, Vector);

	AGhostSwordActor* GhostSwordActor7 = GetWorld()->SpawnActor<AGhostSwordActor>(GetRandomPosition(6), FaceTo);
	GhostSwordActor7->Fire(true, true, this, FocusCharacter, true,Hit_Normal, Vector);

	AGhostSwordActor* GhostSwordActor8 = GetWorld()->SpawnActor<AGhostSwordActor>(GetRandomPosition(7), FaceTo);
	GhostSwordActor8->Fire(true, true, this, FocusCharacter, true,Hit_Normal, Vector);
}

void AVergilCharacter::GhostSword_Normal()
{
	const FVector RandomPosition = GetRandomPosition();
	if(FocusCharacter)
	{
		const FVector ActorLocation = FocusCharacter->GetActorLocation();
		const FRotator FaceTo = (ActorLocation - GetActorLocation()).Rotation();
		AGhostSwordActor* GhostSwordActor = GetWorld()->SpawnActor<AGhostSwordActor>(RandomPosition, FaceTo);
		GhostSwordActor->Fire(true, false, this, FocusCharacter);
	}
}

FVector AVergilCharacter::GetRandomPosition(int32 Index) const
{
	FVector ActorLocation = GetActorLocation();
	const FVector ActorRightVector = GetActorRightVector();
	ActorLocation.Z += 50;
	if(Index == -1)
	{
		Index = FMath::RandRange(1, 8);
	}
	switch (Index)
	{
	case 1:
		{
			FVector Vector = ActorLocation + ActorRightVector * 84;
			Vector.Z += 0;
			return Vector;
		}
	case 2:
		{
			FVector Vector = ActorLocation + ActorRightVector * 60;
			Vector.Z += 30;
			return Vector;
		}
	case 3:
		{
			FVector Vector = ActorLocation + ActorRightVector * 36;
			Vector.Z += 60;
			return Vector;
		}
	case 4:
		{
			FVector Vector = ActorLocation + ActorRightVector * 12;
			Vector.Z += 90;
			return Vector;
		}
	case 5:
		{
			FVector Vector = ActorLocation + ActorRightVector * -12;
			Vector.Z += 90;
			return Vector;
		}
	case 6:
		{
			FVector Vector = ActorLocation + ActorRightVector * -36;
			Vector.Z += 60;
			return Vector;
		}
	case 7:
		{
			FVector Vector = ActorLocation + ActorRightVector * -60;
			Vector.Z += 30;
			return Vector;
		}
	case 8:
		{
			FVector Vector = ActorLocation + ActorRightVector * -84;
			Vector.Z += 0;
			return Vector;
		}
	default:
		{
			FVector Vector = ActorLocation + ActorRightVector * -84;
			Vector.Z += 0;
			return Vector;
		}
	}
}

void AVergilCharacter::LastWeapon()
{
	if(CurrentWeaponIndex == 0)
	{
		CurrentWeaponIndex = WeaponInfos.Num() - 1;
	}else
	{
		CurrentWeaponIndex--;
	}
	GetMesh()->LinkAnimClassLayers(WeaponInfos[CurrentWeaponIndex].AnimClass);
	ShowWeapon();
}

void AVergilCharacter::NextWeapon()
{
	GetMesh()->UnlinkAnimClassLayers(WeaponInfos[CurrentWeaponIndex].AnimClass);
	if(CurrentWeaponIndex == WeaponInfos.Num() - 1)
	{
		CurrentWeaponIndex = 0;
	}else
	{
		CurrentWeaponIndex++;
	}
	GetMesh()->LinkAnimClassLayers(WeaponInfos[CurrentWeaponIndex].AnimClass);
	ShowWeapon();
}

void AVergilCharacter::ShowWeapon() const
{
	if(CurrentWeaponIndex == 0)
	{
		YamatoFullComponent->SetVisibility(true);
		ForceEdgeComponent->SetVisibility(false);
		BeowulfMeshComponent_Hand_L->SetVisibility(false);
		BeowulfMeshComponent_Hand_R->SetVisibility(false);
		BeowulfMeshComponent_Foot_L->SetVisibility(false);
		BeowulfMeshComponent_Foot_R->SetVisibility(false);
	}else if(CurrentWeaponIndex == 1)
	{
		YamatoFullComponent->SetVisibility(false);
		YamatoBladeComponent->SetVisibility(false);
		YamatoScabComponent->SetVisibility(false);
		ForceEdgeComponent->SetVisibility(false);
		BeowulfMeshComponent_Hand_L->SetVisibility(true);
		BeowulfMeshComponent_Hand_R->SetVisibility(true);
		BeowulfMeshComponent_Foot_L->SetVisibility(true);
		BeowulfMeshComponent_Foot_R->SetVisibility(true);
	}else if(CurrentWeaponIndex == 2)
	{
		YamatoFullComponent->SetVisibility(true);
		YamatoBladeComponent->SetVisibility(false);
		YamatoScabComponent->SetVisibility(false);
		ForceEdgeComponent->SetVisibility(true);
		BeowulfMeshComponent_Hand_L->SetVisibility(false);
		BeowulfMeshComponent_Hand_R->SetVisibility(false);
		BeowulfMeshComponent_Foot_L->SetVisibility(false);
		BeowulfMeshComponent_Foot_R->SetVisibility(false);
	}
}

void AVergilCharacter::FocusStart()
{
	bFocusMode = true;
	bResetCameraFinish = false;
	if (AActor* FindActor = UGameplayStatics::GetActorOfClass(GetWorld(),AEnemy001Character::StaticClass()))
	{
		FocusCharacter = Cast<ABaseCharacter>(FindActor);
	}
}

void AVergilCharacter::FocusCompleted()
{
	bFocusMode = false;
	// FocusCharacter = nullptr;
}

void AVergilCharacter::JumpStart()
{
	if(!GetCharacterMovement()->IsFalling())
	{
		BaseActionComponent->FindActionHandlerExec(EWeaponType::None, EActionType::Jump);
	}
}

void AVergilCharacter::MidButtonStart()
{
	if(LastInputDirection == EInputDirection::BackFront)
	{
		BaseActionComponent->FindActionHandlerExec(EWeaponType::None, EActionType::De_Flash);
	}else
	{
		BaseActionComponent->FindActionHandlerExec(EWeaponType::None, EActionType::Flash);
	}
}

void AVergilCharacter::Taunt()
{
	BaseActionComponent->FindActionHandlerExec(EWeaponType::None, EActionType::N_Taunt);
}

void AVergilCharacter::Ex()
{
	BaseActionComponent->FindActionHandlerExec(EWeaponType::Yamato, EActionType::N_Ex);
}

void AVergilCharacter::Landed(const FHitResult& Hit)
{
	
	if (UFlashHandler* FlashHandler = Cast<UFlashHandler>(BaseActionComponent->CurrentHandler))
	{
		if(FlashHandler->HandleAction.ActionLifeCycle == EActionLifeCycle::End)
		{
			BaseActionComponent->FindActionHandlerExec(EWeaponType::None, EActionType::Landed);
			return;
		}
		if(FlashHandler->bFallingAndMiss)
		{
			FlashHandler->Landed();
			return;
		}
		
	}

	if(BaseActionComponent->GetCurrentAction().ActionType == EActionType::N_Combo_A3 && BaseActionComponent->GetCurrentAction().WeaponType == EWeaponType::ForceEdge)
	{
		return;
	}
	
	if(IFallToLanded* FallToLanded = Cast<IFallToLanded>(BaseActionComponent->CurrentHandler))
	{
		FallToLanded->Landed();
		return;
	}
	
	BaseActionComponent->FindActionHandlerExec(EWeaponType::None, EActionType::Landed);
}

void AVergilCharacter::HitEnemyCallBack(ABaseCharacter* Enemy)
{
	
	const FAction CurrentAction = BaseActionComponent->GetCurrentAction();
	if (CurrentAction.WeaponType == Yamato)
	{
		if(CurrentAction.ActionType == EActionType::N_Air_Combo_A1 &&
		CurrentAction.Index == 0) // 空中
		{
			LaunchCharacter(FVector(0,0,180), true, true);
			Enemy->LaunchCharacter(FVector(0,0,250), true, true);
		}
		
	}
	

	
}

void AVergilCharacter::HitEnemyCallBackSingle(ABaseCharacter* Enemy)
{
	const FAction CurrentAction = BaseActionComponent->GetCurrentAction();
	if (CurrentAction.WeaponType == Yamato)
	{
		if(CurrentAction.ActionType == EActionType::N_Front_Attack)
		{
			UConditionTriggerHandler* ConditionTriggerHandler = Cast<UConditionTriggerHandler>(BaseActionComponent->CurrentHandler);
			ConditionTriggerHandler->WhenHit(Enemy);
		}
	}
	
}

void AVergilCharacter::SpawnGhostSwordInVerticalCircleArea(const FVector& Center, const float Radius, const float Height,
                                                           const int32 NumActorsToSpawn)
{
	
	for (int32 i = 0; i < NumActorsToSpawn; i++)
	{
		float RandomAngle = FMath::FRandRange(0.f, 360); // 生成随机角度
		const float RandomDistance = FMath::FRandRange(0, Radius); // 生成随机距离
		float X = Center.X + RandomDistance * FMath::Cos(FMath::DegreesToRadians(RandomAngle));
		float Y = Center.Y + RandomDistance * FMath::Sin(FMath::DegreesToRadians(RandomAngle));
		FVector SpawnLocation = FVector(X, Y, Center.Z + Height);
		AGhostSwordActor* GhostSwordActor  = GetWorld()->SpawnActor<AGhostSwordActor>(SpawnLocation, FRotator(-90, 0, 0));
		GhostSwordActor->Fire(false, true, this, FocusCharacter, true,EActionType::Hit_Silent);
	}
}

void AVergilCharacter::AttackTrace(const FVector& Size, const bool bAttach, const EActionType HitType, const FVector& HitVelocity,
                                   const float FrontDistance, float SilentDuration, bool bPushEnemy, bool bCloseCollision)
{
	
	TArray<FOverlapResult> OverlapResults;
	
	if (UCollisionTraceTool::BoxOverlapTrace(GetWorld(), OverlapResults, GetActorLocation() + GetActorForwardVector() * FrontDistance, Size, GetActorRotation()))
	{
		const FVector Velocity = CalcHitVelocity(HitVelocity);
		for (FOverlapResult OverlapResult : OverlapResults)
		{
			AActor* Actor = OverlapResult.GetActor();
			if (ABaseCharacter* BaseCharacter = Cast<ABaseCharacter>(Actor))
			{
				if(bAttach)
				{
					FVector SafeClosePlace = GetSafeClosePlace(BaseCharacter->GetActorLocation());
					BaseCharacter->TransitionMove(SafeClosePlace, 25);
				}
				HitEnemyCallBack(BaseCharacter);
				if (!HitCharacters.Contains(BaseCharacter) || bPushEnemy)
				{
					if(bCloseCollision)
					{
						SetActorEnableCollision(false);
					}
					HitEnemyCallBackSingle(BaseCharacter);
					HitCharacters.Add(BaseCharacter);
					BaseCharacter->Damage(this, bAttach, HitType, Velocity,SilentDuration);
				}
			}
		}
	}else
	{
		SetActorEnableCollision(true);
	}
}

void AVergilCharacter::AttackTraceEnd()
{
	HitCharacters.Empty();
	SetActorEnableCollision(true);
}

FVector AVergilCharacter::CalcHitVelocity(const FVector& HitVelocity) const
{
	FVector FinalVelocity = GetActorForwardVector() * HitVelocity.Y;
	FinalVelocity.Z = HitVelocity.Z;
	return FinalVelocity;
}

void AVergilCharacter::AdjustCamera(const float DeltaTime)
{
	if(bFocusMode && FocusCharacter && !bIsMovingCamera)
	{

		const FVector EndVector = FocusCharacter->GetActorLocation();
		
		const FVector Location = GetActorLocation();
		
		const float Distance = FVector::Distance(EndVector, Location);
	
		const float Max = FMath::Max(CameraNormalDistance + Distance / 2, CameraNormalDistance + CameraChangeDistance);
		
		const float Lerp = FMath::FInterpTo(CameraBoom->TargetArmLength, Max, DeltaTime, CameraSpeed);
		
		CameraBoom->TargetArmLength = Lerp;
	
		const FVector CenterPointer = (EndVector + Location) / 2;
		
		const FVector ComponentLocation = CameraBoom->GetComponentLocation();
	
		const FVector VInterpTo = FMath::VInterpTo(ComponentLocation, CenterPointer, DeltaTime, CameraSpeed);
	
		CameraBoom->SetWorldLocation(VInterpTo);
		
		if(BaseActionComponent->IsTheHandler(EWeaponType::Beowulf, EActionType::N_Air_Combo_A, Exec, Exec))
		{
			return;
		}
		if(BaseActionComponent->IsTheHandler(EWeaponType::None, EActionType::N_Taunt, Exec, Exec))
		{
			return;
		}
		if(BaseActionComponent->IsTheHandler(EWeaponType::Yamato, EActionType::N_Ex, Exec, End))
		{
			return;
		}
		if(BaseActionComponent->IsTheHandler(EWeaponType::Yamato, EActionType::N_Front_Attack, Exec, After_3))
		{
			return;
		}
		if(BaseActionComponent->IsTheHandler(EWeaponType::ForceEdge, EActionType::N_Front_Attack, Exec, Exec))
		{
			return;
		}

		const FRotator ActorRotation = GetActorRotation();
	
		FRotator EndRotation = (EndVector - Location).Rotation();
	
		EndRotation.Pitch = ActorRotation.Pitch;
	
		EndRotation.Roll = ActorRotation.Roll;
	
		const FRotator RInter = FMath::RInterpTo(ActorRotation, EndRotation, DeltaTime, CameraSpeed * 3);
	
		SetActorRotation(RInter);
	}
}

void AVergilCharacter::ResetCamera(float DeltaTime)
{
	if(!bResetCameraFinish && !bFocusMode)
	{
		const float Lerp = FMath::FInterpTo(CameraBoom->TargetArmLength, CameraDefaultDistance, DeltaTime, CameraSpeed);
		
		CameraBoom->TargetArmLength = Lerp;

		const FVector ComponentLocation = CameraBoom->GetComponentLocation();

		const FVector VInterpTo = FMath::VInterpTo(ComponentLocation, GetActorLocation(), DeltaTime, CameraSpeed);

		CameraBoom->SetWorldLocation(VInterpTo);

		
		if( FMath::Abs(CameraBoom->TargetArmLength - CameraDefaultDistance) < 0.1 &&
			FVector::Distance(ComponentLocation, GetActorLocation()) < 50)
		{
			bResetCameraFinish = true;
		}
	}
	
}


void AVergilCharacter::Tick(float DeltaTime)
{
	AdjustCamera(DeltaTime);
	ResetCamera(DeltaTime);
}











FVector AVergilCharacter::CalcDirectionVector() const
{
	FRotator ControlRotation = GetControlRotation();
	ControlRotation.Pitch = 0;
	ControlRotation.Roll = 0;
	const FQuat Quat = FQuat(ControlRotation);
	const FVector ForwardVector = Quat.GetForwardVector() * MoveAxisValue.Y;
	const FVector RightVector = Quat.GetRightVector() * MoveAxisValue.X;
	return ForwardVector + RightVector;
}

void AVergilCharacter::SetActorDeltaRotator(const float Direction)
{
	const EActionLifeCycle ActionLifeCycle = BaseActionComponent->CurrentHandler->HandleAction.ActionLifeCycle;
	if(BaseActionComponent->CurrentHandler->HandleAction.ActionLifeCycle == Pre_1 ||
		ActionLifeCycle >= After_3)
	{
		const float Delta = FMath::Clamp(Direction,  DeltaRotator * -1, DeltaRotator );
		AddActorLocalRotation(FRotator(0, Delta, 0));
	}
	
}

void AVergilCharacter::BackFrontRecord(float DotFront, float DotRight)
{
	
	if(bFocusMode)
	{
		FocusMoveAxisValue = MoveAxisValue;
		if(MoveAxisValue.Y == 1) // W
		{
			if(DotFront >= 0.5)
			{
				FrontHandle();
			}
			if(DotFront < -0.5)
			{
				FocusMoveAxisValue.X = 0;
				FocusMoveAxisValue.Y = -1;
				BackHandle();
			}
			if(DotRight >= 0.5)
			{
				FocusMoveAxisValue.X = 1;
				FocusMoveAxisValue.Y = 0;
				RightHandle();
			}
			if(DotRight < -0.5)
			{
				FocusMoveAxisValue.X = -1;
				FocusMoveAxisValue.Y = 0;
				LeftHandle();
			}	
		}
		if(MoveAxisValue.Y == -1) // S
		{
			if(DotFront >= 0.5)
			{
				BackHandle();
			}
			if(DotFront < -0.5)
			{
				FocusMoveAxisValue.X = 0;
				FocusMoveAxisValue.Y = 1;
				FrontHandle();
			}
			if(DotRight >= 0.5)
			{
				FocusMoveAxisValue.X = -1;
				FocusMoveAxisValue.Y = 0;
				LeftHandle();
			}
			if(DotRight < -0.5)
			{
				FocusMoveAxisValue.X = 1;
				FocusMoveAxisValue.Y = 0;
				RightHandle();
			}
		}

		if(MoveAxisValue.X == 1) // D
		{
			if(DotFront >= 0.5)
			{
				RightHandle();
			}
			if(DotFront < -0.5)
			{
				FocusMoveAxisValue.X = -1;
				FocusMoveAxisValue.Y = 0;
				LeftHandle();
			}
			if(DotRight >= 0.5)
			{
				FocusMoveAxisValue.X = 0;
				FocusMoveAxisValue.Y = -1;
				BackHandle();
			}
			if(DotRight < -0.5)
			{
				FocusMoveAxisValue.X = 0;
				FocusMoveAxisValue.Y = 1;
				FrontHandle();
			}
		}
		if(MoveAxisValue.X == -1) // A
		{
			if(DotFront >= 0.5)
			{
				LeftHandle();
			}
			if(DotFront < -0.5)
			{
				FocusMoveAxisValue.X = 1;
				FocusMoveAxisValue.Y = 0;
				RightHandle();
			}
			if(DotRight >= 0.5)
			{
				FocusMoveAxisValue.X = 0;
				FocusMoveAxisValue.Y = 1;
				FrontHandle();
			}
			if(DotRight < -0.5)
			{
				FocusMoveAxisValue.X = 0;
				FocusMoveAxisValue.Y = -1;
				BackHandle();
			}
		}
	}
}

float AVergilCharacter::CalcDirection(const FVector& Velocity, const FRotator& BaseRotation)
{
	if (!Velocity.IsNearlyZero())
	{
		const FMatrix RotMatrix = FRotationMatrix(BaseRotation);
		const FVector ForwardVector = RotMatrix.GetScaledAxis(EAxis::X);
		const FVector RightVector = RotMatrix.GetScaledAxis(EAxis::Y);
		const FVector NormalizedVel = Velocity.GetSafeNormal2D();
		const float ForwardCosAngle = FVector::DotProduct(ForwardVector, NormalizedVel);
		float ForwardDeltaDegree = FMath::RadiansToDegrees(FMath::Acos(ForwardCosAngle));
		const float RightCosAngle = FVector::DotProduct(RightVector, NormalizedVel);
		if (RightCosAngle < 0)
		{
			ForwardDeltaDegree *= -1;
		}
		return ForwardDeltaDegree;
	}
	return 0.f;
}

void AVergilCharacter::FrontHandle()
{
	if(LastInputDirection == EInputDirection::Back)
	{
		LastInputDirection = EInputDirection::BackFront;
		CurrentBackFrontThreshold = 0;
	}else if(LastInputDirection == EInputDirection::BackFront)
	{
		if(CurrentBackFrontThreshold >= MaxBackFrontThreshold)
		{
			LastInputDirection = EInputDirection::Front;
		}else
		{
			CurrentBackFrontThreshold++;
		}
	}else
	{
		LastInputDirection = EInputDirection::Front;
	}
}

void AVergilCharacter::BackHandle()
{
	LastInputDirection = EInputDirection::Back;
}

void AVergilCharacter::LeftHandle()
{
	LastInputDirection = Left;
}

void AVergilCharacter::RightHandle()
{
	LastInputDirection = Right;
}

void AVergilCharacter::BindInputMapping(UInputComponent* PlayerInputComponent)
{
	if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent)) {
		EnhancedInputComponent->BindAction(TauntAction, ETriggerEvent::Started, this, &AVergilCharacter::Taunt);
		EnhancedInputComponent->BindAction(ExAction, ETriggerEvent::Started, this, &AVergilCharacter::Ex);
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Started, this, &AVergilCharacter::MoveStart);
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &AVergilCharacter::MoveTriggered);
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Completed, this, &AVergilCharacter::MoveCompleted);
		EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Started, this, &AVergilCharacter::LookStart);
		EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &AVergilCharacter::LookTriggered);
		EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Completed, this, &AVergilCharacter::LookCompleted);
		EnhancedInputComponent->BindAction(ShiftAction, ETriggerEvent::Started, this, &AVergilCharacter::FocusStart);
		EnhancedInputComponent->BindAction(ShiftAction, ETriggerEvent::Completed, this, &AVergilCharacter::FocusCompleted);
		EnhancedInputComponent->BindAction(LeftMouseAction, ETriggerEvent::Started, this, &AVergilCharacter::LeftMouseStart);
		EnhancedInputComponent->BindAction(LeftMouseAction, ETriggerEvent::Triggered, this, &AVergilCharacter::LeftMouseTriggered);
		EnhancedInputComponent->BindAction(LeftMouseAction, ETriggerEvent::Completed, this, &AVergilCharacter::LeftMouseCompleted);
		EnhancedInputComponent->BindAction(LeftMouseAction, ETriggerEvent::Ongoing, this, &AVergilCharacter::LeftMouseOnGoing);
		EnhancedInputComponent->BindAction(SpaceAction, ETriggerEvent::Started, this, &AVergilCharacter::JumpStart);
		EnhancedInputComponent->BindAction(MouseMidButtonAction, ETriggerEvent::Started, this, &AVergilCharacter::MidButtonStart);
		EnhancedInputComponent->BindAction(RightMouseButtonAction, ETriggerEvent::Started, this, &AVergilCharacter::RightMouseStart);
		EnhancedInputComponent->BindAction(RightMouseButtonAction, ETriggerEvent::Triggered, this, &AVergilCharacter::RightMouseTriggered);
		EnhancedInputComponent->BindAction(RightMouseButtonAction, ETriggerEvent::Completed, this, &AVergilCharacter::RightMouseCompleted);
		EnhancedInputComponent->BindAction(RightMouseButtonAction, ETriggerEvent::Ongoing, this, &AVergilCharacter::RightMouseOnGoing);
		EnhancedInputComponent->BindAction(LastWeaponAction, ETriggerEvent::Started, this, &AVergilCharacter::LastWeapon);
		EnhancedInputComponent->BindAction(NextWeaponAction, ETriggerEvent::Started, this, &AVergilCharacter::NextWeapon);
	}
}

void AVergilCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	BindInputMapping(PlayerInputComponent);
}

