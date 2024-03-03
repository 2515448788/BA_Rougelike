// Fill out your copyright notice in the Description page of Project Settings.


#include "Pool/PoolSubsystem.h"
#include "Pool/PoolableInterface.h"


//从对象池中生成Actor 调用函数模板 动态转换类型meta=(DeterminesOutputType="PoolClass", DynamicOutputParam="SpawnedActor")
void UPoolSubsystem::SpawnFromPool(TSubclassOf<AActor> PoolClass, FVector Location, FRotator Rotation,
                                   AActor* Owner, AActor*& SpawnedActor)
{
	SpawnedActor = SpawnFromPool<AActor>(PoolClass, Location, Rotation, Owner);
}

//将Actor返回到对象池中
void UPoolSubsystem::ReturnToPool(AActor* PooledActor)
{
	const UClass* PoolableClass = PooledActor->GetClass();
	//检查传入的对象是否实现了对象池接口
	if (PoolableClass->ImplementsInterface(UPoolableInterface::StaticClass()))
	{
		//执行接口事件-返回时
		IPoolableInterface::Execute_OnReturnToPool(PooledActor);
		//*****返回对象池时需要执行的通用操作*****//
		//1-修改位置
		float RandomX = FMath::FRandRange(-500.0f, 500.0f);
		float RandomY = FMath::FRandRange(-500.0f, 500.0f);
		PooledActor->SetActorLocation(FVector(RandomX, RandomY, -1000.0f));
		//2-隐藏
		PooledActor->SetActorHiddenInGame(true);
		//3-清除Owner
		PooledActor->SetOwner(nullptr);
		//获取对应的对象池列表
		FPoolArray* ObjectPool = ObjectPools.Find(PoolableClass);
		//添加到对象池列表
		ObjectPool->Push(PooledActor);
		//UE_LOG(LogTemp, Warning, TEXT("回到对象池 ObjectPool长度=%d"), ObjectPool->PoolActors.Num());
	}
	else
	{
		//传入的对象没有对象池接口 直接销毁
		PooledActor->Destroy();
	}
}
