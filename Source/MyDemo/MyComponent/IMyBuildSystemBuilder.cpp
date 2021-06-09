// Fill out your copyright notice in the Description page of Project Settings.


#include "IMyBuildSystemBuilder.h" 
#include "Components/InputComponent.h"
#include "ACBuildSystem.h"

FVector IMyBuildSystemBuilder::GetLineTraceOrigin() {
    return FVector::ZeroVector;
}
FRotator IMyBuildSystemBuilder::GetLineTraceRotator() {
    return FRotator::ZeroRotator;
}
UACBuildSystem* IMyBuildSystemBuilder::GetACBuildSystemComponent() {
    if (mybs == nullptr) {
        tpawn = Cast<APawn>(this);
        if (tpawn) {
            UE_LOG(LogClass, Log, TEXT("get pawn"));
            auto comp = tpawn->GetComponentByClass(UACBuildSystem::StaticClass());
            auto build_system_comp = Cast<UACBuildSystem>(comp);
            if (build_system_comp) {
                UE_LOG(LogClass, Log, TEXT("get build system component"));
                mybs = build_system_comp;
                return mybs;
            }
        }
        
        return mybs;
    }
    else {
        return mybs;
    }
}
void IMyBuildSystemBuilder::BindMyBuildSystemAction(UInputComponent* MyInputComponent) {  
    if (GetACBuildSystemComponent() != nullptr) {
        UE_LOG(LogClass, Log, TEXT("get build system component")); 

        DECLARE_DELEGATE_OneParam(FBuildSystemBoolDelegate, const bool);
        MyInputComponent->BindAction<FBuildSystemBoolDelegate>("MyEnableBuildSystem", IE_Pressed, mybs, &UACBuildSystem::EnableThisSystem, true);
        MyInputComponent->BindAction<FBuildSystemBoolDelegate>("MyDisableBuildSystem", IE_Pressed, mybs, &UACBuildSystem::EnableThisSystem, false);
        MyInputComponent->BindAction<FBuildSystemBoolDelegate>("HeingBuildSystemIncreaseCurrentItem", IE_Pressed, mybs, &UACBuildSystem::StepIncCurrentItemIdx, true);
        MyInputComponent->BindAction<FBuildSystemBoolDelegate>("HeingBuildSystemDecreaseCurrentItem", IE_Pressed, mybs, &UACBuildSystem::StepIncCurrentItemIdx, false);
        MyInputComponent->BindAction("HeingBuildSystemPlaceThing", IE_Pressed, mybs, &UACBuildSystem::BuildThing);
        MyInputComponent->BindAction("HeingBuildSystemRot", IE_Pressed, mybs, &UACBuildSystem::InputRotateThing);

    }
}
 

void  IMyBuildSystemBuilder::AddBuildableInfo(FBuildableInfo info) {

    if (GetACBuildSystemComponent() != nullptr) {
        GetACBuildSystemComponent()->AddBuildableInfo(info);
    }
}