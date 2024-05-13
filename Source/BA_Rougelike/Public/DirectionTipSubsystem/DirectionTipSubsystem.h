// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/WorldSubsystem.h"
#include "DirectionTipSubsystem.generated.h"

/**
 * 
 */
UCLASS(Abstract, BlueprintType, Blueprintable)
class BA_ROUGELIKE_API UDirectionTipSubsystem : public UWorldSubsystem, public FTickableGameObject
{
	GENERATED_BODY()
public:
	//初始化
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;
	//Tick
	virtual void Tick(float DeltaTime) override;
	virtual bool IsTickable()const override { return !IsTemplate(); } //判断是否是 CDO，避免执行两次 Tick
	virtual TStatId GetStatId() const override { RETURN_QUICK_DECLARE_CYCLE_STAT(UMyScoreSubsystem, STATGROUP_Tickables); }
	//蓝图事件 初始化完成时调用
	UFUNCTION(BlueprintImplementableEvent, Category = "DirectionTipSubsystem")
	void OnInitialize();
	//蓝图事件 Tick时调用
	UFUNCTION(BlueprintImplementableEvent, Category = "DirectionTipSubsystem")
	void OnTick(float DeltaTime);
};
