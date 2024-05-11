// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/WorldSubsystem.h"
#include "DirectionTipSubsystem.generated.h"

/**
 * 
 */
UCLASS(Abstract, BlueprintType, Blueprintable)
class BA_ROUGELIKE_API UDirectionTipSubsystem : public UWorldSubsystem
{
	GENERATED_BODY()
public:
	//初始化
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;
	//蓝图事件 初始化完成时调用
	UFUNCTION(BlueprintImplementableEvent, Category = "DirectionTipSubsystem")
	void OnInitialize();
};
