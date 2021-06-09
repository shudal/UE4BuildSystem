// Fill out your copyright notice in the Description page of Project Settings.


#include "UWPickableInfo.h"
#include "Components/TextBlock.h"
void UUWPickableInfo::SetPickupTip(FString name, int32 count)
{
	TB_name->SetText(FText::FromString(name));
	TB_count->SetText(FText::FromString(FString::Printf(TEXT("%d"), count)));
}
