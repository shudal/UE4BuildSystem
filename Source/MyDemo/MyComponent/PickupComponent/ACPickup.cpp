// Fill out your copyright notice in the Description page of Project Settings.


#include "ACPickup.h"
#include "IPickup.h"
#include "IPicker.h"

// Sets default values for this component's properties
UACPickup::UACPickup()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UACPickup::BeginPlay()
{
	Super::BeginPlay();

	EnableThisSystem(true);
	// ...
	
}


// Called every frame
void UACPickup::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UACPickup::EnableThisSystem(bool x) {
	if (x) {
		UE_LOG(LogClass, Log, TEXT("enable system"));
		if (bEverInitialized == false) {
			mypawn = (APawn*)GetOwner();
			verifyf(mypawn != nullptr, TEXT("mypawn can not null"));
			picker = Cast<IPicker>(mypawn);
			verifyf(picker != nullptr, TEXT("picker can not null"));

			bEverInitialized = true;
		}
		bEnableThisSystem = true;
	}
	else {
		UE_LOG(LogClass, Log, TEXT("disable system"));
		bEnableThisSystem = false;
	}
}

void UACPickup::PickupArround()
{ 
	UE_LOG(LogClass, Log, TEXT("pick up arround"));
	if (GetWorld()) {

		UE_LOG(LogClass, Log, TEXT("pick up arround 2"));
		FCollisionQueryParams RV_TraceParams = FCollisionQueryParams(FName(TEXT("RV_Trace")), true, mypawn);
		RV_TraceParams.bTraceComplex = false;
		RV_TraceParams.bReturnPhysicalMaterial = false;

		FCollisionObjectQueryParams coqp;
		coqp.AddObjectTypesToQuery(ECollisionChannel::ECC_Pawn);
		coqp.AddObjectTypesToQuery(ECollisionChannel::ECC_WorldStatic);
		coqp.AddObjectTypesToQuery(ECollisionChannel::ECC_WorldDynamic);

		FCollisionShape cs = FCollisionShape::MakeSphere(PICK_DISTANCE);

		TArray<FOverlapResult> Overlaps;
		bool everOverlaped = GetWorld()->OverlapMultiByObjectType(Overlaps, mypawn->GetActorLocation(), FQuat(), coqp, cs, RV_TraceParams);
		if (everOverlaped) {
			for (auto& or : Overlaps) {
				UE_LOG(LogClass, Log, TEXT("pick up arround 4"));
				IPickup* pup = Cast<IPickup>(or.GetActor());
				if (pup) {

					UE_LOG(LogClass, Log, TEXT("collect start"));
					auto info = pup->GetPickupInfo();
					picker->PickUp(info);
					pup->BePickedUp();
				}
			}
			
		}
		else {

			UE_LOG(LogClass, Log, TEXT("pick up arround 3"));
		}
	}
}

