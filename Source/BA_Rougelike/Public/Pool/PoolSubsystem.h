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
	UPROPERTY() //反射标记别忘了
	TMap<UClass*, FPoolArray> ObjectPools;
};


//函数模板-定义 生成对象池对象
template <typename T>
T* UPoolSubsystem::SpawnFromPool(TSubclassOf<AActor> PoolClass, FVector Location, FRotator Rotation, AActor* Owner)
{
	//需要返回的对象---UE5新的指针初始化
	TObjectPtr<T> PooledActor = nullptr;
	// 设置Actor生成参数
	FActorSpawnParameters SpawnParams;
	// 设置碰撞处理方式为尝试调整位置但始终生成
	SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;
	//是否需要对生成的Actor进行后处理
	bool needProcess = true;
	//是否继承了对象池接口
	bool hasPoolInterface = false;
	// 获取Actor类名称
	FString ClassName = PoolClass->GetName();
	//传入的类是否实现了对象池所需的接口
	if (PoolClass.Get()->ImplementsInterface(UPoolableInterface::StaticClass()))
	{
		hasPoolInterface = true;
		//对应类别的对象池数组
		FPoolArray& ObjectPool = ObjectPools.FindOrAdd(PoolClass);
		//对象池列表是否为空
		if (ObjectPool.IsEmpty())
		{
			//对象池列表为空，全新生成Actor
			UE_LOG(LogTemp, Warning, TEXT("PoolSubSystem: 指定类对象池列表为空，重新生成  类名=(%s)"), *ClassName);
			PooledActor = GetWorld()->SpawnActor<T>(PoolClass, Location, Rotation, SpawnParams);
			needProcess = false;
		}
		else
		{
			//检查对象池栈顶元素是否有效
			AActor* PooledObject = ObjectPool.Pop();
			if (IsValid(PooledObject))
			{
				PooledActor = Cast<T>(PooledObject);
			}
			else
			{
				//栈顶元素无效生成新Actor
				UE_LOG(LogTemp, Warning, TEXT("PoolSubSystem: 指定类对象池栈顶元素无效，重新生成 | 类名=(%s)"), *ClassName);
				PooledActor = GetWorld()->SpawnActor<T>(PoolClass, Location, Rotation, SpawnParams);
				needProcess = false;
			}
		}
	}
	//未实现对象池接口 重新生成
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("PoolSubSystem: 指定类未实现对象池接口，重新生成  类名=(%s)"), *ClassName);
		PooledActor = GetWorld()->SpawnActor<T>(PoolClass, Location, Rotation, SpawnParams);
		needProcess = false;
	}
	//后处理
	if (IsValid(PooledActor))
	{
		//设置拥有者
		if (IsValid(Owner))
		{
			PooledActor->SetOwner(Owner);
		}
		if (needProcess)
		{
			//*****从对象池生成时需要执行的通用操作*****//
			//开启Tick
			PooledActor->SetActorTickEnabled(true);
			//设置位置和旋转
			PooledActor->SetActorLocationAndRotation(Location, Rotation);
			//显示出来
			PooledActor->SetActorHiddenInGame(false);
			//开启碰撞
			PooledActor->SetActorEnableCollision(true);
		}
		if (hasPoolInterface)
		{
			//执行接口事件-生成时
			IPoolableInterface::Execute_OnSpawnFromPool(PooledActor);
		}
	}
	//返回获取的Actor
	return PooledActor;
}
