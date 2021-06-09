// Fill out your copyright notice in the Description page of Project Settings.


#include "Pickable.h"
#include "Components/WidgetComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Components/SceneComponent.h"
#include "UWPickableInfo.h"

// Sets default values
APickable::APickable()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//
	MyPickupInfo.count = 1;
	    
	
}

// Called when the game starts or when spawned
void APickable::BeginPlay()
{
	Super::BeginPlay();

	mywid = FindComponentByClass<UWidgetComponent>();
	verify(mywid != nullptr);
	mymesh = FindComponentByClass<UStaticMeshComponent>();
	verify(mymesh != nullptr);

	auto c = mywid->GetWidget(); verify(c); 
	auto w = Cast<UUWPickableInfo>(c); verify(w); 
	w->SetPickupTip(MyPickupInfo.name, MyPickupInfo.count); 

	if (MyPickupInfo.count > 1 || bCanBePicked) {
		mywid->SetVisibility(true);
		
	}
	else {
		mywid->SetVisibility(false);
	}
	
}

// Called every frame
void APickable::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}


FPickupInfo APickable::GetPickupInfo() {
	return MyPickupInfo;
}