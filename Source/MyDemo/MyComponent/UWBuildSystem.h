// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "UWBuildSystem.generated.h"

/**
 * 
 */
UCLASS()
class MYDEMO_API UUWBuildSystem : public UUserWidget
{
	GENERATED_BODY()
	
private:
	class UACBuildSystem* acbs = nullptr;
	class UACBuildSystem* GetBuildSystemComp();
protected:

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		TArray<class UBuildableItem*> items;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (BindWidget))
	class UListView* LVBuildable = nullptr;
public:

	FTimerHandle TimerHandle_DefaultTimer; 
	void UpdateBuildableInfo(); 

	bool Initialize() override;

	void DefaultTimer();


};
