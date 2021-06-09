#include "ACBuildSystem.h"
#include "GameFramework/Pawn.h"

#include "Kismet/GameplayStatics.h" 

#include "Kismet/KismetMathLibrary.h"
#include "IMyBuildSystemBuilder.h"
#include "Components/StaticMeshComponent.h"
#include "Math/UnrealMathUtility.h"

// Sets default values for this component's properties
UACBuildSystem::UACBuildSystem()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	SMCGhost = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("GhostStaticMesh"));
	// ...
}


// Called when the game starts
void UACBuildSystem::BeginPlay()
{
	Super::BeginPlay();

	FRotator r(0, 90, 0);
	auto res = r.RotateVector(FVector(1, 0, 0));
	UE_LOG(LogClass, Log, TEXT("mmm,%s"),*res.ToString());
	//SMCGhost->GetStaticMesh()->SetMaterial(0, GhostMaterial);
	// ... 
}


// Called every frame
void UACBuildSystem::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (IsEnableThisSystem() && GetCurrentItemInfo(tickinfo)) {
		TickLineTrace();
		TickGhost();
	}

	// ...
}

void UACBuildSystem::TickGhost() { 
	FVector SpawnLoc = this->HitLoc;
	FRotator SpawnRot = GetGhostRotator();
	SMCGhost->SetWorldLocationAndRotation(SpawnLoc, SpawnRot);
}
void UACBuildSystem::BuildThing() {

	UE_LOG(LogClass, Log, TEXT("build thing"));
	if (IsEnableThisSystem() == false) return;

	FBuildableInfo thing_info;
	FBuildableInfo* infoptr = nullptr;
	if (GetCurrentItemInfo(thing_info, &infoptr)) {
		verifyf(thing_info.actor_class != nullptr, TEXT("buildable thing actor class can not null"));
		if (GetWorld()) {
			FActorSpawnParameters SpawnParams;
			SpawnParams.Owner = mypawn;
			SpawnParams.Instigator = mypawn->GetInstigator();
			FVector SpawnLoc = this->HitLoc;
			FRotator SpawnRot;
			SpawnRot = GetGhostRotator();
			auto build_thing = GetWorld()->SpawnActor<AActor>(thing_info.actor_class, SpawnLoc, SpawnRot, SpawnParams);
			 
			infoptr->count--;
			if (infoptr->count == 0) {
				RmCurrentItem();
			}
			BuildSysChange();
		}
	}
}
bool UACBuildSystem::GetCurrentItemInfo(FBuildableInfo& thing_info, FBuildableInfo** infoptr) {
	if (build_thing_infos.Num() > 0) {
		verifyf(current_item_idx >= 0 && current_item_idx < build_thing_infos.Num(), TEXT("invalid i"));
		thing_info = build_thing_infos[current_item_idx];

		if (infoptr != nullptr) {
			*infoptr = &build_thing_infos[current_item_idx];
		}
		return true;
	}
	else {
		return false;
	}
}
void UACBuildSystem::RmCurrentItem()
{
	if (build_thing_infos.Num() > 0) { 
		verifyf(current_item_idx >= 0 && current_item_idx < build_thing_infos.Num(), TEXT("invalid i"));
		build_thing_infos.RemoveAt(current_item_idx); 
		StepIncCurrentItemIdx(false);
		BuildSysChange();
	}
	if (build_thing_infos.Num() == 0) {
		SMCGhost->SetStaticMesh(false);
	}
}
void UACBuildSystem::EnableThisSystem(bool x) {
	if (x) {

		UE_LOG(LogClass, Log, TEXT("enable build system"));
		if (bEverInitialized == false) {
			mypawn = (APawn*)GetOwner();
			verifyf(mypawn != nullptr, TEXT("mypawn can not null"));

			mybuilder = Cast<IMyBuildSystemBuilder>(mypawn);
			verifyf(mybuilder != nullptr, TEXT("mybuilder can not null"));

			bEverInitialized = true;
		}
		bEnableThisSystem = true;

		SMCGhost->SetVisibility(true);
	}
	else {

		UE_LOG(LogClass, Log, TEXT("disable build system"));
		bEnableThisSystem = false;

		SMCGhost->SetVisibility(false);
	}

	// for flush
	StepIncCurrentItemIdx(true);
	StepIncCurrentItemIdx(false);
}

bool UACBuildSystem::IncreaseCurrentItemIdx(int32 x) {
	if (IsEnableThisSystem() == false) return false;

	bool ret = false;

	auto nextidx = current_item_idx + x;
	if (nextidx >= 0 && nextidx < build_thing_infos.Num()) {
		current_item_idx = nextidx;
		ret = true;
	}
	else {
		if (FMath::IsNearlyEqual(UKismetMathLibrary::Abs(x), 1.0f)) {
			if (x > 0) current_item_idx = 0;
			else if (build_thing_infos.Num() > 0) current_item_idx = build_thing_infos.Num() - 1;
			else current_item_idx = 0;

			ret = true;
		} 
	}


	FBuildableInfo thing_info;
	if (GetCurrentItemInfo(thing_info)) { 
		SMCGhost->SetStaticMesh(thing_info.SMGhost);
		SMCGhost->SetRelativeScale3D(thing_info.GhostScale);
		TotalRot = 0;
	}


	UE_LOG(LogClass, Log, TEXT("now current item idx : %d"), current_item_idx);
	BuildSysChange();
	return ret;
}

void UACBuildSystem::BuildSysChange() { 
	if (build_sys_changed_delegates.Num() > 0) {
		for (auto& d : build_sys_changed_delegates) {
			d.ExecuteIfBound();
		}
	}
}
void UACBuildSystem::StepIncCurrentItemIdx(const bool inc)
{
	if (inc) {
		IncreaseCurrentItemIdx(1);
	}
	else {
		IncreaseCurrentItemIdx(-1);
	}
}

void UACBuildSystem::InputRotateThing()
{
	RotateThing(LittleRotate);
}

void UACBuildSystem::RotateThing(float x)
{
	int32 tmp = TotalRot + x;
	tmp %= 360;
	TotalRot = tmp;
}

TArray<FBuildableInfo> UACBuildSystem::GetBuildableInfo() const
{
	return build_thing_infos;
}
  

void UACBuildSystem::AddBuildableInfo(FBuildableInfo info)
{
	bool everAdded = false;
	for (auto& i : build_thing_infos) {
		auto p1 = i.actor_class.GetDefaultObject(), p2 = info.actor_class.GetDefaultObject();
		if (p1 != nullptr && p2 != nullptr) {
			if (p1->GetUniqueID() == p2->GetUniqueID()) {
				i.count = i.count + info.count;
				everAdded = true;
			}
		}
	}
	if (!everAdded) { 
		build_thing_infos.Add(info);
		IncreaseCurrentItemIdx(true);
		IncreaseCurrentItemIdx(false);
	}

	BuildSysChange();
}

FRotator UACBuildSystem::GetGhostRotator()
{

	auto rot = UKismetMathLibrary::MakeRotFromZ(HitNormal);
	
	auto xv = FRotationMatrix(rot).GetUnitAxis(EAxis::X);
	auto zaxis = FRotationMatrix(rot).GetUnitAxis(EAxis::Z);
	{
		xv = UKismetMathLibrary::RotateAngleAxis(xv, TotalRot, zaxis);
	}
	auto frot = UKismetMathLibrary::MakeRotFromXZ(xv, HitNormal);

	auto SpawnRot = frot;
	return SpawnRot;
}

void UACBuildSystem::TickLineTrace() {
	FCollisionQueryParams RV_TraceParams = FCollisionQueryParams(FName(TEXT("RV_Trace")), true, mypawn);
	RV_TraceParams.bTraceComplex = false;
	RV_TraceParams.bReturnPhysicalMaterial = true;

	FCollisionObjectQueryParams coqp;
	//coqp.AddObjectTypesToQuery(ECollisionChannel::ECC_Pawn);
	coqp.AddObjectTypesToQuery(ECollisionChannel::ECC_WorldStatic);
	coqp.AddObjectTypesToQuery(ECollisionChannel::ECC_WorldDynamic);


	FVector Start = mybuilder->GetLineTraceOrigin();// = this->GetMesh()->GetSocketLocation("hand_r");
	//Start = GetActorLocation();
	auto Rot = mybuilder->GetLineTraceRotator();
	FVector End = Start + Rot.Vector() * linetrace_distance;
	

	TArray<FHitResult> HitResults;
	bool everHit = GetWorld()->LineTraceMultiByObjectType(
		HitResults,
		Start,
		End,
		coqp,
		RV_TraceParams
	);
	if (everHit && HitResults.Num() > 0) {
		auto wanti = 0;
		for (int32 i = 1; i < HitResults.Num(); i++) {
			if (HitResults[i].bBlockingHit) {
				wanti = i;
				break;
			}
		}
		auto HitRe = HitResults[wanti]; 
		this->HitLoc = HitRe.Location;
		this->HitNormal = HitRe.Normal;
		this->HitActor = HitRe.GetActor(); 
	}
}
 
