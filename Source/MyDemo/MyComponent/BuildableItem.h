// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "ACBuildSystem.h"
#include "BuildableItem.generated.h"

/**
 * 
 */
UCLASS(BlueprintType)
class MYDEMO_API UBuildableItem : public UObject
{
	GENERATED_BODY()
	
public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FBuildableInfo binfo;
};
