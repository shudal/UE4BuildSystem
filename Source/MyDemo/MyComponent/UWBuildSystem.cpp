// Fill out your copyright notice in the Description page of Project Settings.


#include "UWBuildSystem.h"
#include "ACBuildSystem.h"
#include "Components/ListView.h"
#include "BuildableItem.h"
#include "UWBuildableThing.h"

void UUWBuildSystem::UpdateBuildableInfo()
{ 
	if (GetBuildSystemComp()) {
		if (GetBuildSystemComp()->IsEnableThisSystem() == false) {
			return;
		}

		auto infos = GetBuildSystemComp()->GetBuildableInfo();
		items.Empty();
		LVBuildable->ClearListItems();
		if (infos.Num() > 0) { 
			for (auto& i : infos) {
				auto item = NewObject<UBuildableItem>();
				item->binfo = i;
				items.Add(item);
				LVBuildable->AddItem(item);
			}
			 
			auto idx = GetBuildSystemComp()->GetCurrentItemIdx(); 
			verifyf(idx >= 0 && idx < items.Num(), TEXT("idx not valid"));

			for (int32 i = 0; i < items.Num(); i++) { 
				if (i == idx) {  
					LVBuildable->SetItemSelection(items[i], true);
				}
				else { 
					LVBuildable->SetItemSelection(items[i], false);
				}
			} 
		}
		
	}
	 
}
UACBuildSystem* UUWBuildSystem::GetBuildSystemComp() {
	if (acbs == nullptr) {
		auto p = GetOwningLocalPlayer();
		if (p) { 
			auto comp = GetOwningPlayerPawn()->GetComponentByClass(UACBuildSystem::StaticClass());
			if (comp) { 
				auto build_system_comp = Cast<UACBuildSystem>(comp);
				if (build_system_comp) {
					acbs = build_system_comp;
				}
			}
		}
	} 
	return acbs;
}

bool UUWBuildSystem::Initialize() {
	if (!Super::Initialize()) {
		return false;
	}
	if (GetWorld()) {
		GetWorld()->GetTimerManager().SetTimer(TimerHandle_DefaultTimer, this, &UUWBuildSystem::DefaultTimer, 1.0f, true);
		if (GetBuildSystemComp()) {
			UACBuildSystem::FACBuildSystemCurrentItemChangedDelegate d;
			d.BindUObject(this, &UUWBuildSystem::UpdateBuildableInfo);
			GetBuildSystemComp()->build_sys_changed_delegates.Add(d);
		}
	}

	return true;
}

void UUWBuildSystem::DefaultTimer()
{
	//UpdateBuildableInfo();
}
