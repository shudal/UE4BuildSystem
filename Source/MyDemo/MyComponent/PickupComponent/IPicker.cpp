// Fill out your copyright notice in the Description page of Project Settings.


#include "IPicker.h" 
#include "Components/InputComponent.h"
#include "ACPickup.h"

void IPicker::PickUp(FPickupInfo i) {

}

void IPicker::BindMySystemAction(class UInputComponent* MyInputComponent) {
    if (GetComp() != nullptr) {
        MyInputComponent->BindAction("HeingPickupPick", IE_Pressed, GetComp(), &UACPickup::PickupArround);
    }
}

UACPickup* IPicker::GetComp() {
    if (mycomp == nullptr) {
        auto tpawn = Cast<APawn>(this);
        if (tpawn) {
            UE_LOG(LogClass, Log, TEXT("get pawn"));
            auto comp = tpawn->GetComponentByClass(UACPickup::StaticClass());
            mycomp = Cast<UACPickup>(comp);
            if (mycomp) {
                UE_LOG(LogClass, Log, TEXT("get component"));
                return mycomp;
            }
        }

        return mycomp;
    }
    else {
        return mycomp;
    }
} 