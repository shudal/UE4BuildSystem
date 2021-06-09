// Fill out your copyright notice in the Description page of Project Settings.


#include "UWBuildableThing.h" 
#include "Components/EditableTextBox.h" 
#include "Components/TextBlock.h"
#include "Components/Image.h"

void UUWBuildableThing::MyUpdateEntry(FBuildableInfo info)
{
	TB_count->SetText(FText::FromString(FString::Printf(TEXT("%d"), info.count)));
	TB_name->SetText(FText::FromString(info.name));
	ImgIcon->SetBrushFromTexture(info.Icon);
}

void UUWBuildableThing::HightLightMe(const bool h) { 
}