// Fill out your copyright notice in the Description page of Project Settings.


#include "IPickup.h"

void IPickup::BePickedUp()
{
	AActor* a = Cast<AActor>(this);
	a->Destroy();
}
FPickupInfo IPickup::GetPickupInfo() {
	FPickupInfo i;
	return i;
}