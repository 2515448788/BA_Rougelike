// Fill out your copyright notice in the Description page of Project Settings.


#include "DirectionTipSubsystem/DirectionTipSubsystem.h"

void UDirectionTipSubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);
	OnInitialize();
}
