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

	//函数模板-生成对象池对象
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
	// 设置Actor生成参数
	FActorSpawnParameters SpawnParams;
	// 设置碰撞处理方式为尝试调整位置但始终生成
	SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;
	//传入的类是否实现了对象池所需的接口
	if (PoolClass.Get()->ImplementsInterface(UPoolableInterface::StaticClass()))
	{
		FPoolArray& ObjectPool = ObjectPools.FindOrAdd(PoolClass);
		FString ClassName = PoolClass->GetName(); // 获取Actor类名称
		//对象池列表是否为空
		if (ObjectPool.IsEmpty())
		{
			//对象池列表为空，全新生成Actor
			UE_LOG(LogTemp, Warning, TEXT("PoolSubSystem: 对象池列表为空，全新生成  类名=(%s)"), *ClassName);
			PooledActor = GetWorld()->SpawnActor<T>(PoolClass, Location, Rotation, SpawnParams);
		}
		else
		{
			UE_LOG(LogTemp, Log, TEXT("PoolSubSystem: 对象池列表有效，类名=(%s) | Pop前对象池长度(%d)"), *ClassName,
			       ObjectPool.PoolActors.Num());
			//检查对象池栈顶元素是否有效
			AActor* PooledObject = ObjectPool.Pop();
			if (PooledObject == nullptr)
			{
				//栈顶元素无效生成新Actor
				UE_LOG(LogTemp, Warning, TEXT("PoolSubSystem: 栈顶元素无效，重新生成 | 类名=(%s)"), *ClassName);
				PooledActor = GetWorld()->SpawnActor<T>(PoolClass, Location, Rotation, SpawnParams);
			}
			else
			{
				UE_LOG(LogTemp, Log, TEXT("PoolSubSystem: 栈顶元素有效，类名=(%s) | Pop后对象池长度(%d)"), *ClassName,
				       ObjectPool.PoolActors.Num());
				try
				{
					PooledActor = CastChecked<T>(PooledObject);
					UE_LOG(LogTemp, Log, TEXT("PoolSubSystem: 栈顶元素有效，类名=(%s) | 转换类型成功！"), *ClassName);
				}
				catch (const std::bad_cast&)
				{
					UE_LOG(LogTemp, Error, TEXT("PoolSubSystem: 转换PooledObject类型时发生错误 生成新Actor | 类名=(%s)"), *ClassName);
					//生成新Actor
					PooledActor = GetWorld()->SpawnActor<T>(PoolClass, Location, Rotation, SpawnParams);
				}
			}
		}
		//有效性判断
		if (PooledActor != nullptr)
		{
			//*****从对象池生成时需要执行的通用操作*****//
			//1-设置位置和旋转
			PooledActor->SetActorLocationAndRotation(Location, Rotation);
			//2-显示出来
			PooledActor->SetActorHiddenInGame(false);
			//设置拥有者
			if (Owner != nullptr)
			{
				PooledActor->SetOwner(Owner);
			}
			//执行接口事件-生成时
			IPoolableInterface::Execute_OnSpawnFromPool(PooledActor);
		}
	}
	//返回获取的Actor
	return PooledActor;
}
