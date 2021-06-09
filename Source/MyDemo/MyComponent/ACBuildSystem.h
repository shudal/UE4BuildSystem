#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "ACBuildSystem.generated.h"


USTRUCT(BlueprintType)
struct FBuildableInfo
{
	GENERATED_BODY()

		UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int32 count;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FString name;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		TSubclassOf<AActor> actor_class;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		class UStaticMesh* SMGhost;


	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		class UTexture2D* Icon;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FVector GhostScale;
	FBuildableInfo() {
		count = 1;
		name = "NoName";
		actor_class = nullptr;
		SMGhost = nullptr;
		Icon = nullptr;
		GhostScale = FVector::OneVector;
	}
};


UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class MYDEMO_API UACBuildSystem : public UActorComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UACBuildSystem();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	class APawn* mypawn = nullptr;



	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float linetrace_distance = 1500.0f;

	class IMyBuildSystemBuilder* mybuilder = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		TArray<FBuildableInfo> build_thing_infos;


	/**the axis of the static mesh must be on the bottom**/
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		class UStaticMeshComponent* SMCGhost = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		class UMaterial* GhostMaterial = nullptr;


	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float LittleRotate = 15.0f;
public:
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UFUNCTION(BlueprintCallable)
		void BuildThing();

	UFUNCTION(BlueprintCallable)
		void EnableThisSystem(bool x);

	UFUNCTION(BlueprintCallable)
		bool IncreaseCurrentItemIdx(int32 x);
	UFUNCTION(BlueprintCallable)
		void StepIncCurrentItemIdx(const bool inc);
	UFUNCTION(BlueprintCallable)
		void InputRotateThing();

	void RotateThing(float x);

	TArray<FBuildableInfo> GetBuildableInfo() const ;

	
	FORCEINLINE int32 GetCurrentItemIdx() const { return current_item_idx; }

	DECLARE_DELEGATE(FACBuildSystemCurrentItemChangedDelegate);
	TArray< FACBuildSystemCurrentItemChangedDelegate> build_sys_changed_delegates;


	bool IsEnableThisSystem() { return bEnableThisSystem; } 
	void AddBuildableInfo(FBuildableInfo info);
private:
	FRotator GetGhostRotator();
	void TickLineTrace();

	FBuildableInfo tickinfo;
	void TickGhost();

	FVector HitLoc;
	FVector HitNormal;
	class AActor* HitActor = nullptr;

	bool bEverInitialized = false;
	int32 current_item_idx = 0;
	bool GetCurrentItemInfo(FBuildableInfo& thing_info, FBuildableInfo** infoptr = nullptr);
	void RmCurrentItem();
	 
	bool bEnableThisSystem = false;

	float TotalRot = 0.0;

	void BuildSysChange();
};
