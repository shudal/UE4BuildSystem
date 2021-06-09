// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "ACBuildSystem.h"
#include "UWBuildableThing.generated.h"

/**
 * 
 */
UCLASS()
class MYDEMO_API UUWBuildableThing : public UUserWidget
{
	GENERATED_BODY()
	
protected:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (BindWidget))
		class UTextBlock* TB_name = nullptr;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (BindWidget))
		class UTextBlock* TB_count = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (BindWidget))
		class UImage* ImgIcon = nullptr;


	UFUNCTION(BlueprintCallable)
	void MyUpdateEntry(FBuildableInfo info);

	 
public:
	void HightLightMe(const bool h);
};
