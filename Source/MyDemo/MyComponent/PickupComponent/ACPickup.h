// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h" 
#include "ACPickup.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class MYDEMO_API UACPickup : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UACPickup();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;


private:

	bool bEverInitialized = false;
	class IPicker* picker = nullptr;
	class APawn* mypawn = nullptr;
	bool bEnableThisSystem = false;
public:

	bool IsEnableThisSystem() { return bEnableThisSystem; }

	UFUNCTION(BlueprintCallable)
		void EnableThisSystem(bool x);

	UFUNCTION(BlueprintCallable)
		void PickupArround();
protected:

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float PICK_DISTANCE = 300.0f;
};
