// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AttributeSet.h"
#include "AbilitySystemComponent.h"
#include "MyAttributeSet_Character.generated.h"


#define ATTRIBUTE_ACCESSORS(ClassName, PropertyName) \
GAMEPLAYATTRIBUTE_PROPERTY_GETTER(ClassName, PropertyName) \
GAMEPLAYATTRIBUTE_VALUE_GETTER(PropertyName) \
GAMEPLAYATTRIBUTE_VALUE_SETTER(PropertyName) \
GAMEPLAYATTRIBUTE_VALUE_INITTER(PropertyName)


UCLASS()
class BA_ROUGELIKE_API UMyAttributeSet_Character : public UAttributeSet
{
	GENERATED_BODY()

public:
	//血量
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Attributes")
	FGameplayAttributeData Health;
	ATTRIBUTE_ACCESSORS(UMyAttributeSet_Character, Health);
	//最大血量
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Attributes")
	FGameplayAttributeData MaxHealth;
	ATTRIBUTE_ACCESSORS(UMyAttributeSet_Character, MaxHealth);
	//血量再生（每秒自然回血值）
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Attributes")
	FGameplayAttributeData HealthRegeneration;
	ATTRIBUTE_ACCESSORS(UMyAttributeSet_Character, HealthRegeneration);
	//等级
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Attributes")
	FGameplayAttributeData Level;
	ATTRIBUTE_ACCESSORS(UMyAttributeSet_Character, Level);
	//经验值
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Attributes")
	FGameplayAttributeData EXP;
	ATTRIBUTE_ACCESSORS(UMyAttributeSet_Character, EXP);
	//最大经验值 到达最大经验值将经验值EXP归0并升级
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Attributes")
	FGameplayAttributeData MaxEXP;
	ATTRIBUTE_ACCESSORS(UMyAttributeSet_Character, MaxEXP);
	//拾取半径
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Attributes")
	FGameplayAttributeData PickupRadius;
	ATTRIBUTE_ACCESSORS(UMyAttributeSet_Character, PickupRadius);
	//经验倍率
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Attributes")
	FGameplayAttributeData EXPMultiplier;
	ATTRIBUTE_ACCESSORS(UMyAttributeSet_Character, EXPMultiplier);
	//护盾值
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Attributes")
	FGameplayAttributeData EnergyShield;
	ATTRIBUTE_ACCESSORS(UMyAttributeSet_Character, EnergyShield);
	//最大护盾值
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Attributes")
	FGameplayAttributeData MaxEnergyShield;
	ATTRIBUTE_ACCESSORS(UMyAttributeSet_Character, MaxEnergyShield);
	//护盾值再生
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Attributes")
	FGameplayAttributeData EnergyShieldRegeneration;
	ATTRIBUTE_ACCESSORS(UMyAttributeSet_Character, EnergyShieldRegeneration);;
	//减伤率
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Attributes")
	FGameplayAttributeData DamageReductionRate;
	ATTRIBUTE_ACCESSORS(UMyAttributeSet_Character, DamageReductionRate);
	//闪避几率
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Attributes")
	FGameplayAttributeData DodgeChance;
	ATTRIBUTE_ACCESSORS(UMyAttributeSet_Character, DodgeChance);
	//最大闪避几率
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Attributes")
	FGameplayAttributeData MaxDodgeChance;
	ATTRIBUTE_ACCESSORS(UMyAttributeSet_Character, MaxDodgeChance);
	//攻击力
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Attributes")
	FGameplayAttributeData AttackDamage;
	ATTRIBUTE_ACCESSORS(UMyAttributeSet_Character, AttackDamage);
	//伤害倍率
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Attributes")
	FGameplayAttributeData DamageMultiplier;
	ATTRIBUTE_ACCESSORS(UMyAttributeSet_Character, DamageMultiplier);
	//攻击间隔
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Attributes")
	FGameplayAttributeData AttackInterval;
	ATTRIBUTE_ACCESSORS(UMyAttributeSet_Character, AttackInterval);
	//暴击率
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Attributes")
	FGameplayAttributeData CriticalChance;
	ATTRIBUTE_ACCESSORS(UMyAttributeSet_Character, CriticalChance);
	//暴击伤害倍率
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Attributes")
	FGameplayAttributeData CriticalMultiplier;
	ATTRIBUTE_ACCESSORS(UMyAttributeSet_Character, CriticalMultiplier);
	//穿透等级
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Attributes")
	FGameplayAttributeData PenetrationLevel;
	ATTRIBUTE_ACCESSORS(UMyAttributeSet_Character, PenetrationLevel);
	//抛射物反弹次数
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Attributes")
	FGameplayAttributeData ProjectileBounceCount;
	ATTRIBUTE_ACCESSORS(UMyAttributeSet_Character, ProjectileBounceCount);
	//技能冷却缩减
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Attributes")
	FGameplayAttributeData SkillCooldownReduction;
	ATTRIBUTE_ACCESSORS(UMyAttributeSet_Character, SkillCooldownReduction);
	//当前弹匣容量
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Attributes")
	FGameplayAttributeData MagazineSize;
	ATTRIBUTE_ACCESSORS(UMyAttributeSet_Character, MagazineSize);
	//最大弹匣容量
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Attributes")
	FGameplayAttributeData MaxMagazineSize;
	ATTRIBUTE_ACCESSORS(UMyAttributeSet_Character, MaxMagazineSize);

	//AttributeSet自带回调---在Attribute的Current Value被改变时调用
	virtual void PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue) override;
	//AttributeSet自带回调---在Attribute的Base Value被改变时调用
	virtual void PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data) override;
};
