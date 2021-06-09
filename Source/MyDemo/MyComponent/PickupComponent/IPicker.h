// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "IPickup.h"
#include "IPicker.generated.h" 

UINTERFACE(MinimalAPI, Blueprintable)
class UPicker : public UInterface
{
	GENERATED_BODY()
};
/**
 *
 */

class MYDEMO_API IPicker {

	GENERATED_BODY()

private: 
	class UACPickup* GetComp();
protected:
	// do not require ovverride, but must be called in some place
	virtual void BindMySystemAction(class UInputComponent* MyInputComponent);
public:
	// require override
	virtual void PickUp(FPickupInfo i);

private:
	class UACPickup* mycomp = nullptr;
};
