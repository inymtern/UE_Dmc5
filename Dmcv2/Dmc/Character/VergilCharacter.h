// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseCharacter.h"
#include "Dmcv2/Dmc/ActionSystem/BaseActionComponent.h"
#include "VergilCharacter.generated.h"

enum EWeaponType : uint8;
struct FInputActionValue;
class UInputAction;
class UInputMappingContext;
class UCameraComponent;
class USpringArmComponent;
class UNiagaraComponent;

UENUM(BlueprintType)
enum EInputDirection
{
	Nil,
	Front,
	Back,
	BackFront,
	Left,
	Right
};

USTRUCT(BlueprintType)
struct FWeaponInfo
{
	GENERATED_BODY()
	UPROPERTY()
	FString Path;
	UPROPERTY()
	TEnumAsByte<EWeaponType> Weapon;
	UPROPERTY()
	UClass* AnimClass;
};

UCLASS()
class DMCV2_API AVergilCharacter : public ABaseCharacter
{
	GENERATED_BODY()

public:
	AVergilCharacter();

	// ----------------mesh-component-------------------
	
	UPROPERTY(VisibleAnywhere)
	TObjectPtr<USkeletalMeshComponent> HeadMeshComponent;

	UPROPERTY(VisibleAnywhere)
	TObjectPtr<USkeletalMeshComponent> HairMeshComponent;

	UPROPERTY(VisibleAnywhere)
	TObjectPtr<USkeletalMeshComponent> YamatoFullComponent;
	
	UPROPERTY(VisibleAnywhere)
	TObjectPtr<USkeletalMeshComponent> YamatoBladeComponent;
	
	UPROPERTY(VisibleAnywhere)
	TObjectPtr<USkeletalMeshComponent> YamatoScabComponent;

	UPROPERTY(VisibleAnywhere)
	TObjectPtr<USkeletalMeshComponent> ForceEdgeComponent;

	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UNiagaraComponent> BeowulfMeshComponent_Hand_L;

	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UNiagaraComponent> BeowulfMeshComponent_Hand_R;

	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UNiagaraComponent> BeowulfMeshComponent_Foot_R;

	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UNiagaraComponent> BeowulfMeshComponent_Foot_L;

	// --------------------camera--------------------------
	
	UPROPERTY(VisibleAnywhere)
	TObjectPtr<USpringArmComponent> CameraBoom;

	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UCameraComponent> FollowCamera;

	// ----------------------input-------------------------

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Dmc|Input", meta = (AllowPrivateAccess = "true"))
	UInputMappingContext* DefaultMappingContext;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Dmc|Input", meta = (AllowPrivateAccess = "true"))
	UInputAction* MoveAction;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Dmc|Input", meta = (AllowPrivateAccess = "true"))
	UInputAction* LookAction;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Dmc|Input", meta = (AllowPrivateAccess = "true"))
	UInputAction* ShiftAction;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Dmc|Input", meta = (AllowPrivateAccess = "true"))
	UInputAction* SpaceAction;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Dmc|Input", meta = (AllowPrivateAccess = "true"))
	UInputAction* LeftMouseAction;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Dmc|Input", meta = (AllowPrivateAccess = "true"))
	UInputAction* SkillAction;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Dmc|Input", meta = (AllowPrivateAccess = "true"))
	UInputAction* MouseMidButtonAction;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Dmc|Input", meta = (AllowPrivateAccess = "true"))
	UInputAction* RightMouseButtonAction;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Dmc|Input", meta = (AllowPrivateAccess = "true"))
	UInputAction* NextWeaponAction;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Dmc|Input", meta = (AllowPrivateAccess = "true"))
	UInputAction* LastWeaponAction;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Dmc|Input", meta = (AllowPrivateAccess = "true"))
	UInputAction* TauntAction; // 嘲讽
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Dmc|Input", meta = (AllowPrivateAccess = "true"))
	UInputAction* ExAction;  // 大招

	// -----------------move params---------------------
	
	UPROPERTY()
	float DeltaRotator = 5.5f; // 转向速度



	// -------------------input params -------------------
	FTimerHandle InputResetTimerHandle;

	UPROPERTY()
	TEnumAsByte<EInputDirection> LastInputDirection = Nil;
	
	UPROPERTY()
	float ResetDelayTime = 0.18f; // 重置等待时间

	UPROPERTY()
	int8 MaxBackFrontThreshold = 30;
	UPROPERTY()
	int8 CurrentBackFrontThreshold = 0;

	UPROPERTY()
	float CurrentLongPressTime = 0;
	UPROPERTY()
	float CiYuanZhanThreshold = 0.7f;
	UPROPERTY()
	float PerfectCiYuanZhanThreshold = 0.8f;

	// ------------------ camera params ---------------------
	UPROPERTY()
	float YawSpeed = 0.7f;
	UPROPERTY()
	float PitchSpeed = 0.3f;
	UPROPERTY()
	float MinPitchAngle = 335.f;
	UPROPERTY()
	float MaxPitchAngle = 360.f;
	UPROPERTY()
	bool bIsMovingCamera = false; // 是否手动移动相机
	UPROPERTY()
	float CameraSpeed = 3.f;
	UPROPERTY()
	float CameraDefaultDistance = 500.f;
	UPROPERTY()
	float CameraNormalDistance = 600.f;
	UPROPERTY()
	float CameraChangeDistance = 200.f;
	UPROPERTY()
	bool bResetCameraFinish = false;


	// ------------weapon info ----------
	UPROPERTY()
	TArray<FWeaponInfo> WeaponInfos;
	UPROPERTY()
	int8 CurrentWeaponIndex = 0;


	// ----------- attack trace ------

	UPROPERTY()
	TSet<ABaseCharacter*> HitCharacters;

	
	
protected:
	virtual void BeginPlay() override;

	// --- 初始化 ---
	
	void InitializeInput() const;
	void InitializeMeshComponent();
	void InitializeCamera();
	virtual void InitializeActionTable()  override;
	virtual void InitializeActionMapping()  override;
	void InitCharacterSetting();
	
	void InitializeMeshSetting() const;
	void InitializeWeaponSetting();
	void InitializeAnimBlueprintSetting() const;
	


	// --------------- input trigger -----------------
	void BindInputMapping(UInputComponent* PlayerInputComponent);

	void MoveStart(const FInputActionValue& Value);
	void MoveTriggered(const FInputActionValue& Value);
	void MoveCompleted(const FInputActionValue& Value);

	void LookStart(const FInputActionValue& Value);
	void LookTriggered(const FInputActionValue& Value);
	void LookCompleted(const FInputActionValue& Value);

	void LeftMouseStart();
	void LeftMouseTriggered();
	void LeftMouseOnGoing();
	void LeftMouseCompleted();

	void RightMouseStart();
	void RightMouseTriggered();
	void RightMouseOnGoing();
	void RightMouseCompleted();

	void GhostSword_BackFront();
	void GhostSword_Back();
	void GhostSword_Front();
	void GhostSword_Normal();

	FVector GetRandomPosition(int32 Index = -1) const;

	void LastWeapon();
	void NextWeapon();
	void ShowWeapon() const;
	
	void FocusStart();
	void FocusCompleted();


	void JumpStart();
	void MidButtonStart();

	void Taunt();
	void Ex();
	
	virtual void Landed(const FHitResult& Hit) override;
	
	void HitEnemyCallBack(ABaseCharacter* Enemy);
	void HitEnemyCallBackSingle(ABaseCharacter* Enemy);

	void SpawnGhostSwordInVerticalCircleArea(const FVector& Center, float Radius, float Height, int32 NumActorsToSpawn) ;
	
public:

	// ----  check ----
	void AttackTrace(const FVector& Size = FVector(200, 200, 200), bool bAttach = true, EActionType HitType = EActionType::Hit_Normal,
		const FVector& HitVelocity = FVector::Zero(), float FrontDistance = 10, float SilentDuration = 1.5f, bool bPushEnemy = false, bool bCloseCollision = false);
	void AttackTraceEnd();
	FVector CalcHitVelocity(const FVector& HitVelocity) const;
	// ----- calc -----
	FVector CalcDirectionVector() const;
	void SetActorDeltaRotator(const float Direction);
	void BackFrontRecord(float DotFront, float DotRight);
	static float CalcDirection(const FVector& Velocity, const FRotator& BaseRotation);

	// ---- input handle ---
	void FrontHandle();
	void BackHandle();
	void LeftHandle();
	void RightHandle();

	// ---- camera ---
	void AdjustCamera(const float DeltaTime);
	
	void ResetCamera(float DeltaTime);
	
	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
};
