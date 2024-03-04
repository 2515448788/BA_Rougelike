// Fill out your copyright notice in the Description page of Project Settings.


#include "GAS/EnhancedAbilitySystemComponent.h"
#include "InputAction.h"
#include "EnhancedInputComponent.h"
#include "AbilitySystemComponent.h"


/*
 *************注释变量对照表 *************
 *
 * MappedAbilities -> 能力绑定映射表
 * FAbilityInputBinding -> 能力绑定信息（结构体）
 * BoundAbilitiesStack -> 能力句柄列表
 * 
 */


//命名空间 用于获取下一个有效的输入ID
namespace EnhancedInputAbilitySystem_Impl
{
	constexpr int32 InvalidInputID = 0;
	int32 IncrementingInputID = InvalidInputID;

	static int32 GetNextInputID()
	{
		return ++IncrementingInputID;
	}
}


//覆写BeginPlay函数 主要是获取增强输入组件
void UEnhancedInputAbilitySystem::BeginPlay()
{
	Super::BeginPlay(); // 调用父类的BeginPlay函数
	AActor* Owner = GetOwner(); // 获取Owner
	if (IsValid(Owner) && Owner->InputComponent) // 如果Owner存在且有InputComponent
	{
		// 将Owner的输入组件尝试转换为增强输入组件
		InputComponent = CastChecked<UEnhancedInputComponent>(Owner->InputComponent);
	}
}

/**
 * 根据能力的句柄查找能力
 *
 * @param Handle 能力句柄
 * @return 找到的能力指针
 */
FGameplayAbilitySpec* UEnhancedInputAbilitySystem::FindAbilitySpec(FGameplayAbilitySpecHandle Handle)
{
	// 根据句柄查找能力实例
	FGameplayAbilitySpec* FoundAbility = nullptr;
	// 父类函数
	FoundAbility = FindAbilitySpecFromHandle(Handle);
	return FoundAbility;
}

/**
 * 清除指定输入操作绑定的所有能力
 * @param InputAction 要移除的输入动作
 */
void UEnhancedInputAbilitySystem::RemoveEntry(UInputAction* InputAction)
{
	// 从能力绑定映射表中查找传入输入操作对应的能力绑定信息
	if (FAbilityInputBinding* AbilityInputBinding = MappedAbilities.Find(InputAction))
	{
		// 若增强输入组件有效
		if (InputComponent)
		{
			// 移除按下的绑定
			InputComponent->RemoveBindingByHandle(AbilityInputBinding->OnPressedHandle);
			// 移除释放的绑定
			InputComponent->RemoveBindingByHandle(AbilityInputBinding->OnReleasedHandle);
		}
		// 遍历能力句柄列表
		for (FGameplayAbilitySpecHandle AbilityHandle : AbilityInputBinding->BoundAbilitiesStack)
		{
			using namespace EnhancedInputAbilitySystem_Impl;
			// 获取能力实例
			FGameplayAbilitySpec* AbilitySpec = FindAbilitySpec(AbilityHandle);
			// 若能力实例存在且其InputID与能力绑定信息的InputID相同
			if (AbilitySpec && AbilitySpec->InputID == AbilityInputBinding->InputID)
			{
				// 将能力实例InputID设置为0
				AbilitySpec->InputID = InvalidInputID;
			}
		}
		// 从能力绑定映射表中移除对应输入操作的部分
		MappedAbilities.Remove(InputAction);
	}
}

/**
 * 回调函数 输入操作按下时调用
 * @param InputAction 输入动作
 */
void UEnhancedInputAbilitySystem::OnAbilityInputPressed(UInputAction* InputAction)
{
	using namespace EnhancedInputAbilitySystem_Impl;
	// 根据输入操作从能力绑定映射表中查找对应的能力绑定信息
	FAbilityInputBinding* AbilityInputBinding = MappedAbilities.Find(InputAction);
	if (AbilityInputBinding && ensure(AbilityInputBinding->InputID != InvalidInputID))
	{
		// 核心-若传入的能力绑定信息存在且其InputID不等于0 那么调用父类的AbilityLocalInputPressed方法
		AbilityLocalInputPressed(AbilityInputBinding->InputID);
	}
}

/**
 * 回调函数 输入操作松开时调用
 * @param InputAction 输入动作
 */
void UEnhancedInputAbilitySystem::OnAbilityInputReleased(UInputAction* InputAction)
{
	using namespace EnhancedInputAbilitySystem_Impl;
	// 根据输入操作从能力绑定映射表中查找对应的能力绑定信息
	FAbilityInputBinding* AbilityInputBinding = MappedAbilities.Find(InputAction);
	if (AbilityInputBinding && ensure(AbilityInputBinding->InputID != InvalidInputID))
	{
		// 核心-若传入的能力绑定信息存在且其InputID不等于0 那么调用父类的AbilityLocalInputReleased方法
		AbilityLocalInputReleased(AbilityInputBinding->InputID);
	}
}

/**
 * 尝试绑定能力输入
 * @param InputAction 输入动作
 * @param AbilityInputBinding 能力输入绑定
 */
void UEnhancedInputAbilitySystem::TryBindAbilityInput(UInputAction* InputAction,
                                                      FAbilityInputBinding& AbilityInputBinding)
{
	if (InputComponent)
	{
		// 按下事件
		if (AbilityInputBinding.OnPressedHandle == 0)
		{
			//***核心操作 将OnAbilityInputPressed回调函数绑定到输入操作的按下事件***//
			AbilityInputBinding.OnPressedHandle = InputComponent->BindAction(
				InputAction, ETriggerEvent::Started, this, &UEnhancedInputAbilitySystem::OnAbilityInputPressed,
				InputAction).GetHandle();
		}
		// 释放事件
		if (AbilityInputBinding.OnReleasedHandle == 0)
		{
			//***核心操作 将OnAbilityInputReleased回调函数绑定到输入操作的释放事件***//
			AbilityInputBinding.OnReleasedHandle = InputComponent->BindAction(
				InputAction, ETriggerEvent::Completed, this, &UEnhancedInputAbilitySystem::OnAbilityInputReleased,
				InputAction).GetHandle();
		}
	}
}

/**
 * 设置输入绑定
 * @param InputAction 输入动作
 * @param AbilityHandle 能力句柄
 */
void UEnhancedInputAbilitySystem::SetInputBinding(UInputAction* InputAction, FGameplayAbilitySpecHandle AbilityHandle)
{
	using namespace EnhancedInputAbilitySystem_Impl;
	// 通过输入动作查找对应的能力绑定信息
	FAbilityInputBinding* AbilityInputBinding = MappedAbilities.Find(InputAction);
	//当前输入操作存在有效的能力绑定信息
	if (AbilityInputBinding)
	{
		//根据找到的能力绑定信息，获取能力句柄列表的最后一项，并查找其对应的能力实例 （Top函数返回TArray的末尾元素）
		FGameplayAbilitySpec* OldBoundAbility = FindAbilitySpec(AbilityInputBinding->BoundAbilitiesStack.Top());
		if (OldBoundAbility && OldBoundAbility->InputID == AbilityInputBinding->InputID)
		{
			//若能力实例存在且其InputID和当前能力绑定信息的InputID相同 那么旧的能力实例的InputID设置为0
			OldBoundAbility->InputID = InvalidInputID;
		}
	}
	else
	{
		// 当前输入操作无能力绑定信息，则创建一个新的能力绑定信息
		AbilityInputBinding = &MappedAbilities.Add(InputAction);
		// 设置新的能力绑定信息的InputID为下一个可用的InputID
		AbilityInputBinding->InputID = GetNextInputID();
	}
	// 通过能力句柄查找对应的能力实例
	FGameplayAbilitySpec* BindingAbility = FindAbilitySpec(AbilityHandle);
	if (BindingAbility)
	{
		// 将能力实例的InputID设置为对应的能力绑定信息的InputID
		BindingAbility->InputID = AbilityInputBinding->InputID;
	}
	// 将能力句柄添加到能力绑定信息的能力句柄列表中（Push向TArray末尾添加元素）
	AbilityInputBinding->BoundAbilitiesStack.Push(AbilityHandle);
	// 尝试绑定输入动作和对应的能力绑定信息
	TryBindAbilityInput(InputAction, *AbilityInputBinding);
}

/**
 * 清除指定能力绑定的输入操作
 * @param AbilityHandle 能力句柄
 */
void UEnhancedInputAbilitySystem::ClearInputBinding(FGameplayAbilitySpecHandle AbilityHandle)
{
	using namespace EnhancedInputAbilitySystem_Impl;
	//查找传入能力句柄对应的能力实例
	FGameplayAbilitySpec* FoundAbility = FindAbilitySpec(AbilityHandle);
	if (FoundAbility)
	{
		//若传入的能力句柄存在对应的能力实例 那么为 能力绑定映射表 创建迭代器
		auto MappedIterator = MappedAbilities.CreateIterator();
		//遍历
		while (MappedIterator)
		{
			//找到相同的InputID
			if (MappedIterator.Value().InputID == FoundAbility->InputID)
			{
				break;
			}
			//迭代器自增
			++MappedIterator;
		}
		//若迭代器仍有效（表示找到了InputID相同的能力绑定）
		if (MappedIterator)
		{
			//获取找到的能力绑定信息
			FAbilityInputBinding& AbilityInputBinding = MappedIterator.Value();
			//若移除的能力句柄数量大于0
			if (AbilityInputBinding.BoundAbilitiesStack.Remove(AbilityHandle) > 0)
			{
				//剩下的能力句柄列表数量大于0
				if (AbilityInputBinding.BoundAbilitiesStack.Num() > 0)
				{
					//获取最后绑定的能力并尝试将其 InputID 设置为 能力绑定信息 的 InputID
					FGameplayAbilitySpec* StackedAbility = FindAbilitySpec(
						AbilityInputBinding.BoundAbilitiesStack.Top());
					if (StackedAbility && StackedAbility->InputID == 0)
					{
						StackedAbility->InputID = AbilityInputBinding.InputID;
					}
				}
				else
				{
					//该 能力绑定信息 已经没有绑定的能力句柄列表 移除绑定入口
					RemoveEntry(MappedIterator.Key());
				}
				//将传入的能力的InputID重置为0
				FoundAbility->InputID = InvalidInputID;
			}
		}
	}
}

/**
 * 清除指定输入操作绑定的所有能力
 * @param InputAction 输入操作
 */
void UEnhancedInputAbilitySystem::ClearAbilityBindings(UInputAction* InputAction)
{
	RemoveEntry(InputAction);
}
