// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseActionComponent.h"

#include "Dmcv2/Dmc/Character/BaseCharacter.h"
#include "Dmcv2/Dmc/Tools/UPrintTool.h"
#include "Em001Handlers/HitNormalHandler.h"
#include "Handlers/Common/LandedHandler.h"
#include "Handlers/ForceEdge/ForceEdgeComboA1Handler.h"
#include "Handlers/ForceEdge/ForceEdgeComboA2Handler.h"
#include "Handlers/ForceEdge/ForceEdgeComboA3Handler.h"
#include "Handlers/ForceEdge/ForceEdgeComboAHandler.h"
#include "Handlers/Yamato/YamatoAirBackHandler.h"
#include "Handlers/Yamato/YamatoAirComboA1Handler.h"
#include "Handlers/Yamato/YamatoAirComboAHandler.h"
#include "Handlers/Yamato/YamatoBackFrontAttackHandler.h"
#include "Handlers/Yamato/YamatoBackHandler.h"
#include "Handlers/Yamato/YamatoComboA1Handler.h"
#include "Handlers/Yamato/YamatoComboA2Handler.h"
#include "Handlers/Yamato/YamatoComboAHandler.h"
#include "Handlers/Yamato/YamatoFrontHandler.h"


UBaseActionComponent::UBaseActionComponent()
{
	// PrimaryComponentTick.bCanEverTick = true;
}


void UBaseActionComponent::BeginPlay()
{
	AActor* Actor = GetOwner();
	if(!BaseCharacter)
	{
		BaseCharacter = Cast<ABaseCharacter>(Actor);
	}
	
}

FAction UBaseActionComponent::GetCurrentAction()
{
	return CurrentHandler->HandleAction;
}

bool UBaseActionComponent::IsTheHandler(const EWeaponType Weapon, const EActionType Action, const EActionLifeCycle Start,
                                        const EActionLifeCycle End) const
{
	const FAction HandleAction = CurrentHandler->HandleAction;
	return HandleAction.WeaponType == Weapon && HandleAction.ActionType == Action && HandleAction.ActionLifeCycle >= Start && HandleAction.ActionLifeCycle <= End;
}

void UBaseActionComponent::FindAction(FAction& FindAction, const EWeaponType WeaponType, const EActionType ActionType)
{
	FindAction = ActionMapping[WeaponType * 100 + ActionType];
}

UBaseActionHandler* UBaseActionComponent::FindActionHandler(const EWeaponType WeaponType, const EActionType ActionType)
{
	return ActionHandlerMapping[WeaponType * 100 + ActionType];
}

UBaseActionHandler* UBaseActionComponent::FindActionHandlerExec(const EWeaponType WeaponType, const EActionType ActionType)
{
	if (const TObjectPtr<UBaseActionHandler>* ActionHandler = ActionHandlerMapping.Find(WeaponType * 100 + ActionType))
	{
		ActionHandler->Get()->Pre_1();
		return *ActionHandler;
	}
	
	return nullptr;
}


void UBaseActionComponent::SetupActionTable(const FString& Path)
{
	const UDataTable* LoadedDataTable = Cast<UDataTable>(StaticLoadObject(UDataTable::StaticClass(), nullptr, *Path));
	if(!LoadedDataTable)
	{
		UUPrintTool::Error("Load DataTable Failed");
		return;
	}
	TArray<FName> RowNames = LoadedDataTable->GetRowNames();
	for ( const FName RowName : RowNames)
	{
		const FAction* RowData = LoadedDataTable->FindRow<FAction>(RowName, "");
		int Key = RowData->WeaponType * 100 + RowData->ActionType;
		ActionMapping.Add(Key, *RowData);
	}
	
	// BaseCharacter->SetupActionHandlerMapping();
}
void UBaseActionComponent::SetupActionHandlerMapping()
{
	// if(ActionMapping.IsEmpty()) return;
	//
	//
	// UYamatoBackFrontAttackHandler* YamatoBackAttackHandler = NewObject<UYamatoBackFrontAttackHandler>();
	// YamatoBackAttackHandler->Setup(BaseCharacter);
	// ActionHandlerMapping.Add(Yamato * 100 + N_Back_Front_Attack, YamatoBackAttackHandler);
	//
	// UYamatoComboAHandler* YamatoComboAHandler = NewObject<UYamatoComboAHandler>();
	// YamatoComboAHandler->Setup(BaseCharacter);
	// ActionHandlerMapping.Add(Yamato * 100 + N_Combo_A, YamatoComboAHandler);
	//
	// UYamatoComboA1Handler* YamatoComboA1Handler = NewObject<UYamatoComboA1Handler>();
	// YamatoComboA1Handler->Setup(BaseCharacter);
	// ActionHandlerMapping.Add(Yamato * 100 + N_Combo_A1, YamatoComboA1Handler);
	//
	// UForceEdgeComboAHandler* ForceEdgeComboAHandler = NewObject<UForceEdgeComboAHandler>();
	// ForceEdgeComboAHandler->Setup(BaseCharacter);
	// ActionHandlerMapping.Add(ForceEdge * 100 + N_Combo_A, ForceEdgeComboAHandler);
	//
	// UYamatoComboA2Handler* YamatoComboA2Handler = NewObject<UYamatoComboA2Handler>();
	// YamatoComboA2Handler->Setup(BaseCharacter);
	// ActionHandlerMapping.Add(Yamato * 100 + N_Combo_A2, YamatoComboA2Handler);
	//
	// UForceEdgeComboA1Handler* ForceEdgeComboA1Handler = NewObject<UForceEdgeComboA1Handler>();
	// ForceEdgeComboA1Handler->Setup(BaseCharacter);
	// ActionHandlerMapping.Add(ForceEdge * 100 + N_Combo_A1, ForceEdgeComboA1Handler);
	//
	// UForceEdgeComboA2Handler* ForceEdgeComboA2Handler = NewObject<UForceEdgeComboA2Handler>();
	// ForceEdgeComboA2Handler->Setup(BaseCharacter);
	// ActionHandlerMapping.Add(ForceEdge * 100 + N_Combo_A2, ForceEdgeComboA2Handler);
	//
	// UForceEdgeComboA3Handler* ForceEdgeComboA3Handler = NewObject<UForceEdgeComboA3Handler>();
	// ForceEdgeComboA3Handler->Setup(BaseCharacter);
	// ActionHandlerMapping.Add(ForceEdge * 100 + N_Combo_A3, ForceEdgeComboA3Handler);
	//
	// UYamatoBackHandler* YamatoBackHandler = NewObject<UYamatoBackHandler>();
	// YamatoBackHandler->Setup(BaseCharacter);
	// ActionHandlerMapping.Add(Yamato * 100 + N_Back_Attack, YamatoBackHandler);
	//
	// ULandedHandler* LandedHandler = NewObject<ULandedHandler>();
	// LandedHandler->Setup(BaseCharacter);
	// ActionHandlerMapping.Add(None * 100 + Landed, LandedHandler);
	//
	// UYamatoAirComboAHandler* YamatoAirComboAHandler = NewObject<UYamatoAirComboAHandler>();
	// YamatoAirComboAHandler->Setup(BaseCharacter);
	// ActionHandlerMapping.Add(Yamato * 100 + N_Air_Combo_A, YamatoAirComboAHandler);
	//
	// UYamatoAirComboA1Handler* YamatoAirComboA1Handler = NewObject<UYamatoAirComboA1Handler>();
	// YamatoAirComboA1Handler->Setup(BaseCharacter);
	// ActionHandlerMapping.Add(Yamato * 100 + N_Air_Combo_A1, YamatoAirComboA1Handler);
	//
	// UYamatoFrontHandler* YamatoFrontHandler = NewObject<UYamatoFrontHandler>();
	// YamatoFrontHandler->Setup(BaseCharacter);
	// ActionHandlerMapping.Add(Yamato * 100 + N_Front_Attack, YamatoFrontHandler);
	//
	//
	// UYamatoAirBackHandler* YamatoAirBackHandler = NewObject<UYamatoAirBackHandler>();
	// YamatoAirBackHandler->Setup(BaseCharacter);
	// ActionHandlerMapping.Add(Yamato * 100 + N_Air_Back_Attack, YamatoAirBackHandler);
	//
	//
	// UHitNormalHandler* HitNormalHandler = NewObject<UHitNormalHandler>();
	// HitNormalHandler->Setup(BaseCharacter);
	// ActionHandlerMapping.Add(None * 100 + Hit_Normal, HitNormalHandler);
	//
	// CurrentHandler = YamatoBackAttackHandler;
}


void UBaseActionComponent::TickComponent(float DeltaTime, ELevelTick TickType,
                                         FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

