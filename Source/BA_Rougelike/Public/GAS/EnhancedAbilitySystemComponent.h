#pragma once
#include "CoreMinimal.h"
#include "AbilitySystemComponent.h"
#include "GameplayAbilitySpec.h" // for FGameplayAbilitySpecHandle
#include "EnhancedInputComponent.h" // for FInputBindingHandle
#include "EnhancedAbilitySystemComponent.generated.h"

class UInputAction;


/*
 *************注释变量对照表 *************
 *
 * MappedAbilities -> 能力绑定映射表
 * FAbilityInputBinding -> 能力绑定信息（结构体）
 * BoundAbilitiesStack -> 能力句柄列表
 * 
 */


//自定义结构体 储存能力绑定相关信息
USTRUCT()
struct FAbilityInputBinding
{
	GENERATED_BODY()
	int32 InputID = 0; //输入ID
	uint32 OnPressedHandle = 0; //按下操作句柄
	uint32 OnReleasedHandle = 0; //释放操作句柄
	TArray<FGameplayAbilitySpecHandle> BoundAbilitiesStack; //已绑定的能力句柄列表
};

/**
 * 
 */
UCLASS(Blueprintable, BlueprintType, Category = "AbilityInput", meta = (BlueprintSpawnableComponent))
class BA_ROUGELIKE_API UEnhancedInputAbilitySystem : public UAbilitySystemComponent
{
	GENERATED_BODY()

public:
	//绑定能力输入
	UFUNCTION(BlueprintCallable, Category = "Enhanced Input Abilities")
	void SetInputBinding(UInputAction* InputAction, FGameplayAbilitySpecHandle AbilityHandle);
	//清除指定能力绑定的输入操作
	UFUNCTION(BlueprintCallable, Category = "Enhanced Input Abilities")
	void ClearInputBinding(FGameplayAbilitySpecHandle AbilityHandle);
	///清除指定输入操作绑定的所有能力
	UFUNCTION(BlueprintCallable, Category = "Enhanced Input Abilities")
	void ClearAbilityBindings(UInputAction* InputAction);

private:
	virtual void BeginPlay() override;

	FGameplayAbilitySpec* FindAbilitySpec(FGameplayAbilitySpecHandle Handle);

	void RemoveEntry(UInputAction* InputAction);

	void OnAbilityInputPressed(UInputAction* InputAction);

	void OnAbilityInputReleased(UInputAction* InputAction);

	void TryBindAbilityInput(UInputAction* InputAction, FAbilityInputBinding& AbilityInputBinding);


	//能力绑定映射表
	UPROPERTY(transient)
	TMap<UInputAction*, FAbilityInputBinding> MappedAbilities;
	//ASC组件拥有者的增强输入组件
	UPROPERTY(transient)
	UEnhancedInputComponent* InputComponent;
};
