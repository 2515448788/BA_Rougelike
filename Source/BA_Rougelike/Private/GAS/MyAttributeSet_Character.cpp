// Fill out your copyright notice in the Description page of Project Settings.

#include "GAS/MyAttributeSet_Character.h"
#include "GameplayEffectExtension.h"

//AttributeSet自带回调---在Attribute的 CurrentValue 被改变时调用
void UMyAttributeSet_Character::PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue)
{
	Super::PreAttributeChange(Attribute, NewValue);
	//钳制 血量 属性的CurrentValue
	if (Attribute == GetHealthAttribute())
	{
		NewValue = FMath::Clamp(NewValue, 0.0f, GetMaxHealth());
	}
	//钳制 经验值 属性的CurrentValue
	if (Attribute == GetEXPAttribute())
	{
		NewValue = FMath::Clamp(NewValue, 0.0f, GetMaxEXP());
	}
	//钳制 护盾值 属性的CurrentValue
	if (Attribute == GetEnergyShieldAttribute())
	{
		NewValue = FMath::Clamp(NewValue, 0.0f, GetMaxEnergyShield());
	}
	//钳制 闪避几率 属性的CurrentValue
	if (Attribute == GetDodgeChanceAttribute())
	{
		NewValue = FMath::Clamp(NewValue, 0.0f, GetMaxDodgeChance());
	}
	//钳制 弹匣容量 属性的CurrentValue
	if (Attribute == GetMagazineSizeAttribute())
	{
		NewValue = FMath::Clamp(NewValue, 0.0f, GetMaxMagazineSize());
	}
}

//AttributeSet自带回调---在Attribute的 BaseValue 被改变时调用
void UMyAttributeSet_Character::PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data)
{
	Super::PostGameplayEffectExecute(Data);
	//钳制 血量 属性的BaseValue
	if (Data.EvaluatedData.Attribute == GetHealthAttribute())
	{
		SetHealth(FMath::Clamp(GetHealth(), 0.0f, GetMaxHealth()));
	}
	//钳制 经验值 属性的BaseValue
	if (Data.EvaluatedData.Attribute == GetEXPAttribute())
	{
		SetEXP(FMath::Clamp(GetEXP(), 0.0f, GetMaxEXP()));
	}
	//钳制 护盾值 属性的BaseValue
	if (Data.EvaluatedData.Attribute == GetEnergyShieldAttribute())
	{
		SetEnergyShield(FMath::Clamp(GetEnergyShield(), 0.0f, GetMaxEnergyShield()));
	}
	//钳制 闪避几率 属性的BaseValue
	if (Data.EvaluatedData.Attribute == GetDodgeChanceAttribute())
	{
		SetDodgeChance(FMath::Clamp(GetDodgeChance(), 0.0f, GetMaxDodgeChance()));
	}
	//钳制 弹匣容量 属性的BaseValue
	if (Data.EvaluatedData.Attribute == GetMagazineSizeAttribute())
	{
		SetMagazineSize(FMath::Clamp(GetMagazineSize(), 0.0f, GetMaxMagazineSize()));
	}
}
