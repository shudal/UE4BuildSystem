// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h" 
#include "IPickup.h" 
#include "IPickup.generated.h" 

UINTERFACE(MinimalAPI, Blueprintable)
class UPickup : public UInterface
{
	GENERATED_BODY()
};
/**
 * 
 */


USTRUCT(BlueprintType)
struct FPickupInfo
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
	FPickupInfo() {
		count = 1;
		name = "NoName";
		actor_class = nullptr;
		SMGhost = nullptr;
		Icon = nullptr;
		GhostScale = FVector::OneVector;
	}
};
class MYDEMO_API IPickup
{
	GENERATED_BODY()
public:
	virtual FPickupInfo GetPickupInfo();
	virtual void BePickedUp();
};
