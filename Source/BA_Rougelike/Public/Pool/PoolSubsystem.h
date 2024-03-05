// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PoolableInterface.h"
#include "Subsystems/WorldSubsystem.h"
#include "PoolSubsystem.generated.h"


//自定义结构体 用于对象池Map中
USTRUCT()
struct FPoolArray
{
	GENERATED_BODY()
	UPROPERTY()
	TArray<AActor*> PoolActors;
	//自定义函数 对象池列表是否为空
	bool IsEmpty() const
	{
		return PoolActors.IsEmpty();
	}

	// 自定义函数 从列表取出对象
	AActor* Pop()
	{
		return PoolActors.Pop();
	}

	//自定义函数 向列表添加对象
	void Push(AActor* PooledActor)
	{
		PoolActors.Push(PooledActor);
	}
};

UCLASS()
class BA_ROUGELIKE_API UPoolSubsystem : public UWorldSubsystem
{
	GENERATED_BODY()

public:
	//从对象池中生成Actor 调用函数模板 动态转换类型meta=(DeterminesOutputType="PoolClass", DynamicOutputParam="SpawnedActor")
	UFUNCTION(BlueprintCallable, Category="PoolSubsystem",
		meta=(DeterminesOutputType="PoolClass", DynamicOutputParam="SpawnedActor"))
	void SpawnFromPool(TSubclassOf<AActor> PoolClass, FVector Location, FRotator Rotation,
	                   AActor* Owner, AActor*& SpawnedActor);

	//函数模板 生成对象池对象
	template <typename T>
	T* SpawnFromPool(TSubclassOf<AActor> PoolClass, FVector Location, FRotator Rotation,
	                 AActor* Owner);

	//将Actor返回到对象池中
	UFUNCTION(BlueprintCallable, Category="PoolSubsystem")
	void ReturnToPool(AActor* PooledActor);

	//对象池Map  每个类有自己的对象池物体列表
	TMap<UClass*, FPoolArray> ObjectPools;
};


//函数模板-定义 生成对象池对象
template <typename T>
T* UPoolSubsystem::SpawnFromPool(TSubclassOf<AActor> PoolClass, FVector Location, FRotator Rotation, AActor* Owner)
{
	//需要返回的对象
	T* PooledActor = nullptr;
	//传入的类是否实现了对象池所需的接口
	if (PoolClass.Get()->ImplementsInterface(UPoolableInterface::StaticClass()))
	{
		FPoolArray& ObjectPool = ObjectPools.FindOrAdd(PoolClass);
		//对象池列表是否为空
		if (ObjectPool.IsEmpty())
		{
			//UE_LOG(LogTemp, Warning, TEXT("对象池列表为空 全新生成"));
			//为空 生成新的Actor
			FActorSpawnParameters SpawnParams;
			//设置碰撞处理方式 尝试调整位置 但固定生成
			SpawnParams.SpawnCollisionHandlingOverride =
				ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;
			//生成Actor
			PooledActor = GetWorld()->SpawnActor<T>(PoolClass, Location, Rotation, SpawnParams);
			//执行接口事件-生成时
			IPoolableInterface::Execute_OnSpawnFromPool(PooledActor);
		}
		else
		{
			//UE_LOG(LogTemp, Warning, TEXT("对象池列表不是空的 从对象池Pop前 对象池当前长度=%d"), ObjectPool.PoolActors.Num());
			//不为空 从列表中获取一个Actor 并转换为模板所需类型
			PooledActor = CastChecked<T>(ObjectPool.Pop());
			//UE_LOG(LogTemp, Warning, TEXT("对象池列表不是空的 从对象池Pop后 对象池当前长度=%d"), ObjectPool.PoolActors.Num());
			//*****从对象池生成时需要执行的通用操作*****//
			//1-设置位置和旋转
			PooledActor->SetActorLocationAndRotation(Location, Rotation);
			//2-显示出来
			PooledActor->SetActorHiddenInGame(false);
		}
		//设置拥有者
		if (Owner != nullptr)
		{
			PooledActor->SetOwner(Owner);
		}
		//执行接口事件-生成时
		IPoolableInterface::Execute_OnSpawnFromPool(PooledActor);
	}
	//返回获取的Actor
	return PooledActor;
}
