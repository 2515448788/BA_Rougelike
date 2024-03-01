// Fill out your copyright notice in the Description page of Project Settings.


#include "GAS/EnhancedAbilitySystemComponent.h"
#include "InputAction.h"
#include "EnhancedInputComponent.h"
#include "AbilitySystemComponent.h"
#include "AbilitySystemGlobals.h"

namespace EnhancedInputAbilitySystem_Impl
{
	constexpr int32 InvalidInputID = 0;
	int32 IncrementingInputID = InvalidInputID;

	static int32 GetNextInputID()
	{
		return ++IncrementingInputID;
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
	// 查找能力句柄对应的FGameplayAbilitySpec对象
	FGameplayAbilitySpec* BindingAbility = FindAbilitySpec(AbilityHandle);
	// 查找输入动作对应的FAbilityInputBinding对象
	FAbilityInputBinding* AbilityInputBinding = MappedAbilities.Find(InputAction);
	// 如果存在对应的FAbilityInputBinding对象
	if (AbilityInputBinding)
	{
		// 获取当前绑定的FGameplayAbilitySpec对象
		FGameplayAbilitySpec* OldBoundAbility = FindAbilitySpec(AbilityInputBinding->BoundAbilitiesStack.Top());
		// 如果当前绑定的FGameplayAbilitySpec对象与输入动作对应的FGameplayAbilitySpec对象相同
		if (OldBoundAbility && OldBoundAbility->InputID == AbilityInputBinding->InputID)
		{
			// 将当前绑定的FGameplayAbilitySpec对象的InputID设置为无效值
			OldBoundAbility->InputID = InvalidInputID;
		}
	}
	else
	{
		// 如果不存在对应的FAbilityInputBinding对象，则创建一个新的FAbilityInputBinding对象
		AbilityInputBinding = &MappedAbilities.Add(InputAction);
		// 设置新的FAbilityInputBinding对象的InputID为下一个可用的InputID
		AbilityInputBinding->InputID = GetNextInputID();
	}
	// 如果存在对应的FGameplayAbilitySpec对象
	if (BindingAbility)
	{
		// 将FGameplayAbilitySpec对象的InputID设置为对应的FAbilityInputBinding对象的InputID
		BindingAbility->InputID = AbilityInputBinding->InputID;
	}
	// 将能力句柄添加到FAbilityInputBinding对象的BoundAbilitiesStack中
	AbilityInputBinding->BoundAbilitiesStack.Push(AbilityHandle);
	// 尝试绑定输入动作和对应的FAbilityInputBinding对象
	TryBindAbilityInput(InputAction, *AbilityInputBinding);
}


/**
 * 清除输入绑定
 * @param AbilityHandle 能力句柄
 */
void UEnhancedInputAbilitySystem::ClearInputBinding(FGameplayAbilitySpecHandle AbilityHandle)
{
	using namespace EnhancedInputAbilitySystem_Impl;
	if (FGameplayAbilitySpec* FoundAbility = FindAbilitySpec(AbilityHandle))
	{
		auto MappedIterator = MappedAbilities.CreateIterator();
		while (MappedIterator)
		{
			if (MappedIterator.Value().InputID == FoundAbility->InputID)
			{
				break;
			}
			++MappedIterator;
		}

		if (MappedIterator)
		{
			FAbilityInputBinding& AbilityInputBinding = MappedIterator.Value();
			if (AbilityInputBinding.BoundAbilitiesStack.Remove(AbilityHandle) > 0)
			{
				if (AbilityInputBinding.BoundAbilitiesStack.Num() > 0)
				{
					FGameplayAbilitySpec* StackedAbility = FindAbilitySpec(
						AbilityInputBinding.BoundAbilitiesStack.Top());
					if (StackedAbility && StackedAbility->InputID == 0)
					{
						StackedAbility->InputID = AbilityInputBinding.InputID;
					}
				}
				else
				{
					RemoveEntry(MappedIterator.Key());
				}
				FoundAbility->InputID = InvalidInputID;
			}
		}
	}
}


/**
 * 清除指定输入动作的绑定
 * @param InputAction 要清除绑定的输入动作
 */
void UEnhancedInputAbilitySystem::ClearAbilityBindings(UInputAction* InputAction)
{
	RemoveEntry(InputAction); // 从系统中移除指定的输入动作
}


/**
 * 当能力输入按下时的回调函数
 * @param InputAction 输入动作
 */
void UEnhancedInputAbilitySystem::OnAbilityInputPressed(UInputAction* InputAction)
{
	using namespace EnhancedInputAbilitySystem_Impl;
	// 查找与输入动作对应的绑定
	FAbilityInputBinding* FoundBinding = MappedAbilities.Find(InputAction);
	if (FoundBinding && ensure(FoundBinding->InputID != InvalidInputID))
	{
		// 调用父类方法
		AbilityLocalInputPressed(FoundBinding->InputID);
	}
}


// 尝试通过输入操作调用父类的AbilityLocalInputReleased方法
void UEnhancedInputAbilitySystem::OnAbilityInputReleased(UInputAction* InputAction)
{
	using namespace EnhancedInputAbilitySystem_Impl;
	// 查找与输入操作对应的AbilityInputBinding
	FAbilityInputBinding* FoundBinding = MappedAbilities.Find(InputAction);
	if (FoundBinding && ensure(FoundBinding->InputID != InvalidInputID))
	{
		// 调用父类的AbilityLocalInputReleased方法
		AbilityLocalInputReleased(FoundBinding->InputID);
	}
}


/**
 * @brief 从映射的技能列表中移除指定的输入动作
 * 
 * @param InputAction 要移除的输入动作
 */
void UEnhancedInputAbilitySystem::RemoveEntry(UInputAction* InputAction)
{
	// 查找输入动作对应的绑定
	if (FAbilityInputBinding* Bindings = MappedAbilities.Find(InputAction))
	{
		// 如果存在输入组件
		if (InputComponent)
		{
			// 移除按下的绑定
			InputComponent->RemoveBindingByHandle(Bindings->OnPressedHandle);
			// 移除释放的绑定
			InputComponent->RemoveBindingByHandle(Bindings->OnReleasedHandle);
		}
		// 遍历绑定的技能栈
		for (FGameplayAbilitySpecHandle AbilityHandle : Bindings->BoundAbilitiesStack)
		{
			// 使用增强输入能力系统插件的命名空间
			using namespace EnhancedInputAbilitySystem_Impl;

			// 查找对应的技能规范
			FGameplayAbilitySpec* AbilitySpec = FindAbilitySpec(AbilityHandle);
			// 如果找到对应的技能规范且输入ID与绑定的输入ID相同
			if (AbilitySpec && AbilitySpec->InputID == Bindings->InputID)
			{
				// 将输入ID设置为无效值
				AbilitySpec->InputID = InvalidInputID;
			}
		}
		// 从映射的技能列表中移除输入动作
		MappedAbilities.Remove(InputAction);
	}
}


/**
 * 根据能力规格的句柄查找能力规格
 *
 * @param Handle 能力规格的句柄
 * @return 找到的能力规格指针
 */
FGameplayAbilitySpec* UEnhancedInputAbilitySystem::FindAbilitySpec(FGameplayAbilitySpecHandle Handle)
{
	// 从句柄中查找能力规格
	FGameplayAbilitySpec* FoundAbility = nullptr;
	FoundAbility = FindAbilitySpecFromHandle(Handle);
	return FoundAbility;
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
			AbilityInputBinding.OnPressedHandle = InputComponent->BindAction(
				InputAction, ETriggerEvent::Started, this, &UEnhancedInputAbilitySystem::OnAbilityInputPressed,
				InputAction).GetHandle();
		}
		// 释放事件
		if (AbilityInputBinding.OnReleasedHandle == 0)
		{
			AbilityInputBinding.OnReleasedHandle = InputComponent->BindAction(
				InputAction, ETriggerEvent::Completed, this, &UEnhancedInputAbilitySystem::OnAbilityInputReleased,
				InputAction).GetHandle();
		}
	}
}

/**
 * @brief UEnhancedInputAbilitySystem::BeginPlay函数的实现
 */
void UEnhancedInputAbilitySystem::BeginPlay()
{
	Super::BeginPlay(); // 调用父类的BeginPlay函数
	AActor* Owner = GetOwner(); // 获取Owner
	if (IsValid(Owner) && Owner->InputComponent) // 如果Owner存在且有InputComponent
	{
		// 将Owner的InputComponent转换为UEnhancedInputComponent类型并赋值给InputComponent
		InputComponent = CastChecked<UEnhancedInputComponent>(Owner->InputComponent);
	}
}
