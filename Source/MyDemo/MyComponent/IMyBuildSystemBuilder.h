// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "IMyBuildSystemBuilder.generated.h" 

UINTERFACE(MinimalAPI, Blueprintable)
class UMyBuildSystemBuilder : public UInterface
{
	GENERATED_BODY()
};

/**
 *
 */
class MYDEMO_API IMyBuildSystemBuilder
{
	GENERATED_BODY()

private:
	class UACBuildSystem* mybs = nullptr;
	class APawn* tpawn = nullptr;
	class UACBuildSystem* GetACBuildSystemComponent();

protected:
	virtual void BindMyBuildSystemAction(class UInputComponent* MyInputComponent);
	virtual void AddBuildableInfo(struct FBuildableInfo info);
public:
	virtual FVector GetLineTraceOrigin();
	virtual FRotator GetLineTraceRotator();
	
};
