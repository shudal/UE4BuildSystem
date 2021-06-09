// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "IPickup.h"
#include "Pickable.generated.h"

UCLASS()
class MYDEMO_API APickable : public AActor,public IPickup
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APickable();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

protected:

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FPickupInfo MyPickupInfo;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		bool bCanBePicked = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		class UWidgetComponent* mywid = nullptr;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		class UStaticMeshComponent* mymesh = nullptr;
	
public:

	virtual FPickupInfo GetPickupInfo() override;
};
