// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "GAS/EnhancedAbilitySystemComponent.h"
#include "AbilitySystemInterface.h"
#include "MyCharacterBase.generated.h"

UCLASS()
class BA_ROUGELIKE_API AMyCharacterBase : public ACharacter, public IAbilitySystemInterface
{
	GENERATED_BODY()

public:
	//构造函数
	AMyCharacterBase();
	//事件开始时
	virtual void BeginPlay() override;
	//ASC组件
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "EnhancedAbilitySystem")
	UEnhancedInputAbilitySystem* EnhancedInputAbilitySystem;
	//接口函数 获取ASC
	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;

	//属性改变回调---血量
	void OnHealthChanged(const FOnAttributeChangeData& Data);
	//委托-属性变化时进行广播---血量
	DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnHealthChanged, float, NewValue);

	UPROPERTY(BlueprintAssignable, Category = "EnhancedAbilitySystem")
	FOnHealthChanged HealthChangedEvent;

	//属性改变回调---最大血量
	void OnMaxHealthChanged(const FOnAttributeChangeData& Data);
	//委托-属性变化时进行广播---最大血量
	DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnMaxHealthChanged, float, NewValue);

	UPROPERTY(BlueprintAssignable, Category = "EnhancedAbilitySystem")
	FOnMaxHealthChanged MaxHealthChangedEvent;

	//属性改变回调---血量再生
	void OnHealthRegenerationChanged(const FOnAttributeChangeData& Data);
	//委托-属性变化时进行广播---血量再生
	DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnHealthRegenerationChanged, float, NewValue);

	UPROPERTY(BlueprintAssignable, Category = "EnhancedAbilitySystem")
	FOnHealthRegenerationChanged HealthRegenerationChangedEvent;

	//属性改变回调---等级
	void OnLevelChanged(const FOnAttributeChangeData& Data);
	//委托-属性变化时进行广播---等级
	DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FLevelChanged, float, NewValue);

	UPROPERTY(BlueprintAssignable, Category = "EnhancedAbilitySystem")
	FLevelChanged LevelChangedEvent;

	//属性改变回调---经验值
	void OnEXPChanged(const FOnAttributeChangeData& Data);
	//委托-属性变化时进行广播---经验值
	DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FEXPChanged, float, NewValue);

	UPROPERTY(BlueprintAssignable, Category = "EnhancedAbilitySystem")
	FEXPChanged EXPChangedEvent;

	//属性改变回调---最大经验值
	void OnMaxEXPChanged(const FOnAttributeChangeData& Data);
	//委托-属性变化时进行广播---最大经验值
	DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FMaxEXPChanged, float, NewValue);

	UPROPERTY(BlueprintAssignable, Category = "EnhancedAbilitySystem")
	FMaxEXPChanged MaxEXPChangedEvent;

	//属性改变回调---拾取半径
	void OnPickupRadiusChanged(const FOnAttributeChangeData& Data);
	//委托-属性变化时进行广播---拾取半径
	DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FPickupRadiusChanged, float, NewValue);

	UPROPERTY(BlueprintAssignable, Category = "EnhancedAbilitySystem")
	FPickupRadiusChanged PickupRadiusChangedEvent;

	//属性改变回调---经验倍率
	void OnEXPMultiplierChanged(const FOnAttributeChangeData& Data);
	//委托-属性变化时进行广播---经验倍率
	DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FEXPMultiplierChanged, float, NewValue);

	UPROPERTY(BlueprintAssignable, Category = "EnhancedAbilitySystem")
	FEXPMultiplierChanged EXPMultiplierChangedEvent;

	//属性改变回调---护盾值
	void OnEnergyShieldChanged(const FOnAttributeChangeData& Data);
	//委托-属性变化时进行广播---护盾值
	DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FEnergyShieldChanged, float, NewValue);

	UPROPERTY(BlueprintAssignable, Category = "EnhancedAbilitySystem")
	FEnergyShieldChanged EnergyShieldChangedEvent;

	//属性改变回调---最大护盾值
	void OnMaxEnergyShieldChanged(const FOnAttributeChangeData& Data);
	//委托-属性变化时进行广播---最大护盾值
	DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FMaxEnergyShieldChanged, float, NewValue);

	UPROPERTY(BlueprintAssignable, Category = "EnhancedAbilitySystem")
	FMaxEnergyShieldChanged MaxEnergyShieldChangedEvent;

	//属性改变回调---护盾值再生
	void OnEnergyShieldRegenerationChanged(const FOnAttributeChangeData& Data);
	//委托-属性变化时进行广播---护盾值再生
	DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FEnergyShieldRegenerationChanged, float, NewValue);

	UPROPERTY(BlueprintAssignable, Category = "EnhancedAbilitySystem")
	FEnergyShieldRegenerationChanged EnergyShieldRegenerationChangedEvent;

	//属性改变回调---减伤率
	void OnDamageReductionRateChanged(const FOnAttributeChangeData& Data);
	//委托-属性变化时进行广播---减伤率
	DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FDamageReductionRateChanged, float, NewValue);

	UPROPERTY(BlueprintAssignable, Category = "EnhancedAbilitySystem")
	FDamageReductionRateChanged DamageReductionRateChangedEvent;

	//属性改变回调---闪避几率
	void OnDodgeChanceChanged(const FOnAttributeChangeData& Data);
	//委托-属性变化时进行广播---闪避几率
	DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FDodgeChanceChanged, float, NewValue);

	UPROPERTY(BlueprintAssignable, Category = "EnhancedAbilitySystem")
	FDodgeChanceChanged DodgeChanceChangedEvent;

	//属性改变回调---最大闪避几率
	void OnMaxDodgeChanceChanged(const FOnAttributeChangeData& Data);
	//委托-属性变化时进行广播---最大闪避几率
	DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FMaxDodgeChanceChanged, float, NewValue);

	UPROPERTY(BlueprintAssignable, Category = "EnhancedAbilitySystem")
	FMaxDodgeChanceChanged MaxDodgeChanceChangedEvent;

	//属性改变回调---攻击力
	void OnAttackDamageChanged(const FOnAttributeChangeData& Data);
	//委托-属性变化时进行广播---攻击力
	DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FAttackDamageChanged, float, NewValue);

	UPROPERTY(BlueprintAssignable, Category = "EnhancedAbilitySystem")
	FAttackDamageChanged AttackDamageChangedEvent;

	//属性改变回调---伤害倍率
	void OnDamageMultiplierChanged(const FOnAttributeChangeData& Data);
	//委托-属性变化时进行广播---伤害倍率
	DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FDamageMultiplierChanged, float, NewValue);

	UPROPERTY(BlueprintAssignable, Category = "EnhancedAbilitySystem")
	FDamageMultiplierChanged DamageMultiplierChangedEvent;

	//属性改变回调---攻击间隔
	void OnAttackIntervalChanged(const FOnAttributeChangeData& Data);
	//委托-属性变化时进行广播---攻击间隔
	DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FAttackIntervalChanged, float, NewValue);

	UPROPERTY(BlueprintAssignable, Category = "EnhancedAbilitySystem")
	FAttackIntervalChanged AttackIntervalChangedEvent;

	//属性改变回调---暴击率
	void OnCriticalChanceChanged(const FOnAttributeChangeData& Data);
	//委托-属性变化时进行广播---暴击率
	DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FCriticalChanceChanged, float, NewValue);

	UPROPERTY(BlueprintAssignable, Category = "EnhancedAbilitySystem")
	FCriticalChanceChanged CriticalChanceChangedEvent;

	//属性改变回调---暴击伤害倍率
	void OnCriticalMultiplierChanged(const FOnAttributeChangeData& Data);
	//委托-属性变化时进行广播---暴击伤害倍率
	DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FCriticalMultiplierChanged, float, NewValue);

	UPROPERTY(BlueprintAssignable, Category = "EnhancedAbilitySystem")
	FCriticalMultiplierChanged CriticalMultiplierChangedEvent;

	//属性改变回调---穿透等级
	void OnPenetrationLevelChanged(const FOnAttributeChangeData& Data);
	//委托-属性变化时进行广播---穿透等级
	DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FPenetrationLevelChanged, float, NewValue);

	UPROPERTY(BlueprintAssignable, Category = "EnhancedAbilitySystem")
	FPenetrationLevelChanged PenetrationLevelChangedEvent;

	//属性改变回调---抛射物反弹次数
	void OnProjectileBounceCountChanged(const FOnAttributeChangeData& Data);
	//委托-属性变化时进行广播---抛射物反弹次数
	DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FProjectileBounceCountChanged, float, NewValue);

	UPROPERTY(BlueprintAssignable, Category = "EnhancedAbilitySystem")
	FProjectileBounceCountChanged ProjectileBounceCountChangedEvent;

	//属性改变回调---技能冷却缩减
	void OnSkillCooldownReductionChanged(const FOnAttributeChangeData& Data);
	//委托-属性变化时进行广播---技能冷却缩减
	DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FSkillCooldownReductionChanged, float, NewValue);

	UPROPERTY(BlueprintAssignable, Category = "EnhancedAbilitySystem")
	FSkillCooldownReductionChanged SkillCooldownReductionChangedEvent;

	//属性改变回调---当前弹匣容量
	void OnMagazineSizeChanged(const FOnAttributeChangeData& Data);
	//委托-属性变化时进行广播---当前弹匣容量
	DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FMagazineSizeChanged, float, NewValue);

	UPROPERTY(BlueprintAssignable, Category = "EnhancedAbilitySystem")
	FMagazineSizeChanged MagazineSizeChangedEvent;

	//属性改变回调---最大弹匣容量
	void OnMaxMagazineSizeChanged(const FOnAttributeChangeData& Data);
	//委托-属性变化时进行广播---最大弹匣容量
	DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FMaxMagazineSizeChanged, float, NewValue);

	UPROPERTY(BlueprintAssignable, Category = "EnhancedAbilitySystem")
	FMaxMagazineSizeChanged MaxMagazineSizeChangedEvent;
};
