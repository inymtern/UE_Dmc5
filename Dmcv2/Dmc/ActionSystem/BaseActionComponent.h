// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "BaseActionComponent.generated.h"

class UBaseActionHandler;

UENUM(BlueprintType)
enum EActionType : uint8
{
	Default,
	N_Combo_A,
	N_Combo_A1,
	N_Combo_A2,
	N_Combo_A3,
	N_Back_Attack,
	N_Front_Attack,

	S_ForceEdge_Front_Attack_After,
	S_ForceEdge_Back_Front_Attack_After,
	
	N_Back_Front_Attack,
	N_Air_Back_Attack,
	N_Air_Front_Attack,
	N_Air_Back_Front_Attack,
	N_Air_Combo_A,
	N_Air_Combo_A1,
	N_Long_Press,

	N_Taunt,
	N_Ex,

	
	Landed,
	Jump,
	Flash,
	De_Flash,
	Attack_Flash,
	
	Hit_Normal,
	Hit_Vector,
	Hit_Silent,
	Hit_Land,
	Hit_Getup
};

UENUM(BlueprintType)
enum EActionLifeCycle : uint8
{
	Pre_1 = 0,
	Pre_2 = 1,
	Pre_3 = 2,
	
	Exec = 3,

	After_1 = 10,
	After_2 = 11,
	After_3 = 12,
	End = 13
};

UENUM(BlueprintType)
enum EWeaponType : uint8
{
	None = 0,
	Yamato = 1,
	Beowulf = 2,
	ForceEdge = 3
};


USTRUCT(BlueprintType)
struct FAnim
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TObjectPtr<UAnimSequence> AnimSequence;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	bool bLoop = false;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float PlayRate = 1;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TEnumAsByte<EActionType> SubActionType;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FVector HitVector = FVector(1, 0, 0);
};


USTRUCT(BlueprintType)
struct FAction : public FTableRowBase
{
	GENERATED_BODY()

	FAction(): ActionType(Hit_Normal), WeaponType(Yamato), ActionLifeCycle(End), CurrentAnim()
	{
	}

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TEnumAsByte<EActionType> ActionType;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TEnumAsByte<EWeaponType> WeaponType;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TArray<FAnim> AnimArray;

	UPROPERTY(BlueprintReadOnly)
	TEnumAsByte<EActionLifeCycle> ActionLifeCycle;

	UPROPERTY()
	int Index = 0; // 第几个动画

	UPROPERTY()
	FAnim CurrentAnim;
};

class ABaseCharacter;

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class DMCV2_API UBaseActionComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UBaseActionComponent();
	
	UPROPERTY()
	TObjectPtr<ABaseCharacter> BaseCharacter;

	UPROPERTY()
	TObjectPtr<UBaseActionHandler> CurrentHandler;

	UPROPERTY()
	TMap<int, FAction> ActionMapping;

	UPROPERTY()
	TMap<int, TObjectPtr<UBaseActionHandler>> ActionHandlerMapping;

	UPROPERTY()
	bool bToggleSignal = false; // 切换动作信号

	

protected:
	virtual void BeginPlay() override;

public:

	FAction GetCurrentAction();

	bool IsTheHandler(EWeaponType Weapon, EActionType Action, EActionLifeCycle Start = Exec, EActionLifeCycle End = Exec) const;
	
	void FindAction(FAction& FindAction, EWeaponType WeaponType, EActionType ActionType);

	UBaseActionHandler* FindActionHandler(EWeaponType WeaponType, EActionType ActionType);
	
	UBaseActionHandler* FindActionHandlerExec(EWeaponType WeaponType, EActionType ActionType);
	
	void SetupActionTable(const FString& Path);

	void SetupActionHandlerMapping();
	
	virtual void TickComponent(float DeltaTime, ELevelTick TickType,
	                           FActorComponentTickFunction* ThisTickFunction) override;
};
