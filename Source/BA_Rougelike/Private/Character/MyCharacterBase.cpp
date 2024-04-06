// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/MyCharacterBase.h"

#include "GAS/MyAttributeSet_Character.h"

// Sets default values
AMyCharacterBase::AMyCharacterBase()
{
	//实例化ASC
	EnhancedInputAbilitySystem = CreateDefaultSubobject<
		UEnhancedInputAbilitySystem>(TEXT("EnhancedInputAbilitySystem"));
}

//事件开始时
void AMyCharacterBase::BeginPlay()
{
	Super::BeginPlay();
	//绑定属性变化回调 内部广播委托
	if (EnhancedInputAbilitySystem != nullptr)
	{
		//初始化ASC
		EnhancedInputAbilitySystem->InitAbilityActorInfo(this, this);
		//获取ASC组件里对应属性变化的委托并绑定自己定义的回调---血量
		FOnGameplayAttributeValueChange& HealthChangeDelegate = EnhancedInputAbilitySystem->
			GetGameplayAttributeValueChangeDelegate(UMyAttributeSet_Character::GetHealthAttribute());
		HealthChangeDelegate.AddUObject(this, &AMyCharacterBase::OnHealthChanged);
		//获取ASC组件里对应属性变化的委托并绑定自己定义的回调---最大血量
		FOnGameplayAttributeValueChange& MaxHealthChangeDelegate = EnhancedInputAbilitySystem->
			GetGameplayAttributeValueChangeDelegate(UMyAttributeSet_Character::GetMaxHealthAttribute());
		MaxHealthChangeDelegate.AddUObject(this, &AMyCharacterBase::OnMaxHealthChanged);
		//获取ASC组件里对应属性变化的委托并绑定自己定义的回调---血量再生（每秒自然回血值）
		FOnGameplayAttributeValueChange& HealthRegenerationChangeDelegate = EnhancedInputAbilitySystem->
			GetGameplayAttributeValueChangeDelegate(UMyAttributeSet_Character::GetHealthRegenerationAttribute());
		HealthRegenerationChangeDelegate.AddUObject(this, &AMyCharacterBase::OnHealthRegenerationChanged);
		//获取ASC组件里对应属性变化的委托并绑定自己定义的回调---等级
		FOnGameplayAttributeValueChange& LevelChangeDelegate = EnhancedInputAbilitySystem->
			GetGameplayAttributeValueChangeDelegate(UMyAttributeSet_Character::GetLevelAttribute());
		LevelChangeDelegate.AddUObject(this, &AMyCharacterBase::OnLevelChanged);
		//获取ASC组件里对应属性变化的委托并绑定自己定义的回调---经验值
		FOnGameplayAttributeValueChange& EXPChangeDelegate = EnhancedInputAbilitySystem->
			GetGameplayAttributeValueChangeDelegate(UMyAttributeSet_Character::GetEXPAttribute());
		EXPChangeDelegate.AddUObject(this, &AMyCharacterBase::OnEXPChanged);
		//获取ASC组件里对应属性变化的委托并绑定自己定义的回调---最大经验值 到达最大经验值将经验值EXP归0并升级
		FOnGameplayAttributeValueChange& MaxEXPChangeDelegate = EnhancedInputAbilitySystem->
			GetGameplayAttributeValueChangeDelegate(UMyAttributeSet_Character::GetMaxEXPAttribute());
		MaxEXPChangeDelegate.AddUObject(this, &AMyCharacterBase::OnMaxEXPChanged);
		//获取ASC组件里对应属性变化的委托并绑定自己定义的回调---拾取半径
		FOnGameplayAttributeValueChange& PickupRadiusChangeDelegate = EnhancedInputAbilitySystem->
			GetGameplayAttributeValueChangeDelegate(UMyAttributeSet_Character::GetPickupRadiusAttribute());
		PickupRadiusChangeDelegate.AddUObject(this, &AMyCharacterBase::OnPickupRadiusChanged);
		//获取ASC组件里对应属性变化的委托并绑定自己定义的回调---经验倍率
		FOnGameplayAttributeValueChange& EXPMultiplierChangeDelegate = EnhancedInputAbilitySystem->
			GetGameplayAttributeValueChangeDelegate(UMyAttributeSet_Character::GetEXPMultiplierAttribute());
		EXPMultiplierChangeDelegate.AddUObject(this, &AMyCharacterBase::OnEXPMultiplierChanged);
		//获取ASC组件里对应属性变化的委托并绑定自己定义的回调---护盾值
		FOnGameplayAttributeValueChange& EnergyShieldChangeDelegate = EnhancedInputAbilitySystem->
			GetGameplayAttributeValueChangeDelegate(UMyAttributeSet_Character::GetEnergyShieldAttribute());
		EnergyShieldChangeDelegate.AddUObject(this, &AMyCharacterBase::OnEnergyShieldChanged);
		//获取ASC组件里对应属性变化的委托并绑定自己定义的回调---最大护盾值
		FOnGameplayAttributeValueChange& MaxEnergyShieldChangeDelegate = EnhancedInputAbilitySystem->
			GetGameplayAttributeValueChangeDelegate(UMyAttributeSet_Character::GetMaxEnergyShieldAttribute());
		MaxEnergyShieldChangeDelegate.AddUObject(this, &AMyCharacterBase::OnMaxEnergyShieldChanged);
		//获取ASC组件里对应属性变化的委托并绑定自己定义的回调---护盾值再生
		FOnGameplayAttributeValueChange& EnergyShieldRegenerationChangeDelegate = EnhancedInputAbilitySystem->
			GetGameplayAttributeValueChangeDelegate(UMyAttributeSet_Character::GetEnergyShieldRegenerationAttribute());
		EnergyShieldRegenerationChangeDelegate.AddUObject(this, &AMyCharacterBase::OnEnergyShieldRegenerationChanged);
		//获取ASC组件里对应属性变化的委托并绑定自己定义的回调---减伤率
		FOnGameplayAttributeValueChange& DamageReductionRateChangeDelegate = EnhancedInputAbilitySystem->
			GetGameplayAttributeValueChangeDelegate(UMyAttributeSet_Character::GetDamageReductionRateAttribute());
		DamageReductionRateChangeDelegate.AddUObject(this, &AMyCharacterBase::OnDamageReductionRateChanged);
		//获取ASC组件里对应属性变化的委托并绑定自己定义的回调---闪避几率
		FOnGameplayAttributeValueChange& DodgeChanceChangeDelegate = EnhancedInputAbilitySystem->
			GetGameplayAttributeValueChangeDelegate(UMyAttributeSet_Character::GetDodgeChanceAttribute());
		DodgeChanceChangeDelegate.AddUObject(this, &AMyCharacterBase::OnDodgeChanceChanged);
		//获取ASC组件里对应属性变化的委托并绑定自己定义的回调---最大闪避几率
		FOnGameplayAttributeValueChange& MaxDodgeChanceChangeDelegate = EnhancedInputAbilitySystem->
			GetGameplayAttributeValueChangeDelegate(UMyAttributeSet_Character::GetMaxDodgeChanceAttribute());
		MaxDodgeChanceChangeDelegate.AddUObject(this, &AMyCharacterBase::OnMaxDodgeChanceChanged);
		//获取ASC组件里对应属性变化的委托并绑定自己定义的回调---攻击力
		FOnGameplayAttributeValueChange& AttackDamageChangeDelegate = EnhancedInputAbilitySystem->
			GetGameplayAttributeValueChangeDelegate(UMyAttributeSet_Character::GetAttackDamageAttribute());
		AttackDamageChangeDelegate.AddUObject(this, &AMyCharacterBase::OnAttackDamageChanged);
		//获取ASC组件里对应属性变化的委托并绑定自己定义的回调---伤害倍率
		FOnGameplayAttributeValueChange& DamageMultiplierChangeDelegate = EnhancedInputAbilitySystem->
			GetGameplayAttributeValueChangeDelegate(UMyAttributeSet_Character::GetDamageMultiplierAttribute());
		DamageMultiplierChangeDelegate.AddUObject(this, &AMyCharacterBase::OnDamageMultiplierChanged);
		//获取ASC组件里对应属性变化的委托并绑定自己定义的回调---攻击间隔
		FOnGameplayAttributeValueChange& AttackSpeedMultiplierChangeDelegate = EnhancedInputAbilitySystem->
			GetGameplayAttributeValueChangeDelegate(UMyAttributeSet_Character::GetAttackSpeedMultiplierAttribute());
		AttackSpeedMultiplierChangeDelegate.AddUObject(this, &AMyCharacterBase::OnAttackSpeedMultiplierChanged);
		//获取ASC组件里对应属性变化的委托并绑定自己定义的回调---暴击率
		FOnGameplayAttributeValueChange& CriticalChanceChangeDelegate = EnhancedInputAbilitySystem->
			GetGameplayAttributeValueChangeDelegate(UMyAttributeSet_Character::GetCriticalChanceAttribute());
		CriticalChanceChangeDelegate.AddUObject(this, &AMyCharacterBase::OnCriticalChanceChanged);
		//获取ASC组件里对应属性变化的委托并绑定自己定义的回调---暴击伤害倍率
		FOnGameplayAttributeValueChange& CriticalMultiplierChangeDelegate = EnhancedInputAbilitySystem->
			GetGameplayAttributeValueChangeDelegate(UMyAttributeSet_Character::GetCriticalMultiplierAttribute());
		CriticalMultiplierChangeDelegate.AddUObject(this, &AMyCharacterBase::OnCriticalMultiplierChanged);
		//获取ASC组件里对应属性变化的委托并绑定自己定义的回调---穿透等级
		FOnGameplayAttributeValueChange& PenetrationLevelChangeDelegate = EnhancedInputAbilitySystem->
			GetGameplayAttributeValueChangeDelegate(UMyAttributeSet_Character::GetPenetrationLevelAttribute());
		PenetrationLevelChangeDelegate.AddUObject(this, &AMyCharacterBase::OnPenetrationLevelChanged);
		//获取ASC组件里对应属性变化的委托并绑定自己定义的回调---抛射物反弹次数
		FOnGameplayAttributeValueChange& ProjectileBounceCountChangeDelegate = EnhancedInputAbilitySystem->
			GetGameplayAttributeValueChangeDelegate(UMyAttributeSet_Character::GetProjectileBounceCountAttribute());
		ProjectileBounceCountChangeDelegate.AddUObject(this, &AMyCharacterBase::OnProjectileBounceCountChanged);
		//获取ASC组件里对应属性变化的委托并绑定自己定义的回调---技能冷却缩减
		FOnGameplayAttributeValueChange& SkillCooldownReductionChangeDelegate = EnhancedInputAbilitySystem->
			GetGameplayAttributeValueChangeDelegate(UMyAttributeSet_Character::GetSkillCooldownReductionAttribute());
		SkillCooldownReductionChangeDelegate.AddUObject(this, &AMyCharacterBase::OnSkillCooldownReductionChanged);
		//获取ASC组件里对应属性变化的委托并绑定自己定义的回调---移动速度
		FOnGameplayAttributeValueChange& MoveSpeedChangeDelegate = EnhancedInputAbilitySystem->
			GetGameplayAttributeValueChangeDelegate(UMyAttributeSet_Character::GetMoveSpeedAttribute());
		MoveSpeedChangeDelegate.AddUObject(this, &AMyCharacterBase::OnMoveSpeedChanged);
		//获取ASC组件里对应属性变化的委托并绑定自己定义的回调---子弹初速
		FOnGameplayAttributeValueChange& ProjectileInitSpeedChangeDelegate = EnhancedInputAbilitySystem->
			GetGameplayAttributeValueChangeDelegate(UMyAttributeSet_Character::GetProjectileInitSpeedAttribute());
		ProjectileInitSpeedChangeDelegate.AddUObject(this, &AMyCharacterBase::OnProjectileInitSpeedChanged);
		//获取ASC组件里对应属性变化的委托并绑定自己定义的回调---子弹初速
		FOnGameplayAttributeValueChange& AttackRangeChangeDelegate = EnhancedInputAbilitySystem->
			GetGameplayAttributeValueChangeDelegate(UMyAttributeSet_Character::GetAttackRangeAttribute());
		AttackRangeChangeDelegate.AddUObject(this, &AMyCharacterBase::OnAttackRangeChanged);
	}
}

//GAS接口函数 获取ASC
UAbilitySystemComponent* AMyCharacterBase::GetAbilitySystemComponent() const
{
	return EnhancedInputAbilitySystem;
}

//回调定义 属性变化时广播对应委托 --- 血量
void AMyCharacterBase::OnHealthChanged(const FOnAttributeChangeData& Data)
{
	if (Data.OldValue == Data.NewValue)
	{
		return;
	}
	HealthChangedEvent.Broadcast(Data.OldValue, Data.NewValue);
}

//回调定义 属性变化时广播对应委托 --- 最大血量
void AMyCharacterBase::OnMaxHealthChanged(const FOnAttributeChangeData& Data)
{
	if (Data.OldValue == Data.NewValue)
	{
		return;
	}
	MaxHealthChangedEvent.Broadcast(Data.OldValue, Data.NewValue);
}

//回调定义 属性变化时广播对应委托 --- 血量再生
void AMyCharacterBase::OnHealthRegenerationChanged(const FOnAttributeChangeData& Data)
{
	if (Data.OldValue == Data.NewValue)
	{
		return;
	}
	HealthRegenerationChangedEvent.Broadcast(Data.OldValue, Data.NewValue);
}

//回调定义 属性变化时广播对应委托 --- 等级
void AMyCharacterBase::OnLevelChanged(const FOnAttributeChangeData& Data)
{
	if (Data.OldValue == Data.NewValue)
	{
		return;
	}
	LevelChangedEvent.Broadcast(Data.OldValue, Data.NewValue);
}

//回调定义 属性变化时广播对应委托 --- 经验值
void AMyCharacterBase::OnEXPChanged(const FOnAttributeChangeData& Data)
{
	if (Data.OldValue == Data.NewValue)
	{
		return;
	}
	EXPChangedEvent.Broadcast(Data.OldValue, Data.NewValue);
}

//回调定义 属性变化时广播对应委托 --- 最大经验值
void AMyCharacterBase::OnMaxEXPChanged(const FOnAttributeChangeData& Data)
{
	if (Data.OldValue == Data.NewValue)
	{
		return;
	}
	MaxEXPChangedEvent.Broadcast(Data.OldValue, Data.NewValue);
}

//回调定义 属性变化时广播对应委托 --- 拾取半径
void AMyCharacterBase::OnPickupRadiusChanged(const FOnAttributeChangeData& Data)
{
	if (Data.OldValue == Data.NewValue)
	{
		return;
	}
	PickupRadiusChangedEvent.Broadcast(Data.OldValue, Data.NewValue);
}

//回调定义 属性变化时广播对应委托 --- 经验倍率
void AMyCharacterBase::OnEXPMultiplierChanged(const FOnAttributeChangeData& Data)
{
	if (Data.OldValue == Data.NewValue)
	{
		return;
	}
	EXPMultiplierChangedEvent.Broadcast(Data.OldValue, Data.NewValue);
}

//回调定义 属性变化时广播对应委托 --- 护盾值
void AMyCharacterBase::OnEnergyShieldChanged(const FOnAttributeChangeData& Data)
{
	if (Data.OldValue == Data.NewValue)
	{
		return;
	}
	EnergyShieldChangedEvent.Broadcast(Data.OldValue, Data.NewValue);
}

//回调定义 属性变化时广播对应委托 --- 最大护盾值
void AMyCharacterBase::OnMaxEnergyShieldChanged(const FOnAttributeChangeData& Data)
{
	if (Data.OldValue == Data.NewValue)
	{
		return;
	}
	MaxEnergyShieldChangedEvent.Broadcast(Data.OldValue, Data.NewValue);
}

//回调定义 属性变化时广播对应委托 --- 护盾值再生
void AMyCharacterBase::OnEnergyShieldRegenerationChanged(const FOnAttributeChangeData& Data)
{
	if (Data.OldValue == Data.NewValue)
	{
		return;
	}
	EnergyShieldRegenerationChangedEvent.Broadcast(Data.OldValue, Data.NewValue);
}

//回调定义 属性变化时广播对应委托 --- 减伤率
void AMyCharacterBase::OnDamageReductionRateChanged(const FOnAttributeChangeData& Data)
{
	if (Data.OldValue == Data.NewValue)
	{
		return;
	}
	DamageReductionRateChangedEvent.Broadcast(Data.OldValue, Data.NewValue);
}

//回调定义 属性变化时广播对应委托 --- 闪避几率
void AMyCharacterBase::OnDodgeChanceChanged(const FOnAttributeChangeData& Data)
{
	if (Data.OldValue == Data.NewValue)
	{
		return;
	}
	DodgeChanceChangedEvent.Broadcast(Data.OldValue, Data.NewValue);
}

//回调定义 属性变化时广播对应委托 --- 最大闪避几率
void AMyCharacterBase::OnMaxDodgeChanceChanged(const FOnAttributeChangeData& Data)
{
	if (Data.OldValue == Data.NewValue)
	{
		return;
	}
	MaxDodgeChanceChangedEvent.Broadcast(Data.OldValue, Data.NewValue);
}

//回调定义 属性变化时广播对应委托 --- 攻击力
void AMyCharacterBase::OnAttackDamageChanged(const FOnAttributeChangeData& Data)
{
	if (Data.OldValue == Data.NewValue)
	{
		return;
	}
	AttackDamageChangedEvent.Broadcast(Data.OldValue, Data.NewValue);
}

//回调定义 属性变化时广播对应委托 --- 伤害倍率
void AMyCharacterBase::OnDamageMultiplierChanged(const FOnAttributeChangeData& Data)
{
	if (Data.OldValue == Data.NewValue)
	{
		return;
	}
	DamageMultiplierChangedEvent.Broadcast(Data.OldValue, Data.NewValue);
}

//回调定义 属性变化时广播对应委托 --- 攻击间隔
void AMyCharacterBase::OnAttackSpeedMultiplierChanged(const FOnAttributeChangeData& Data)
{
	if (Data.OldValue == Data.NewValue)
	{
		return;
	}
	AttackSpeedMultiplierChangedEvent.Broadcast(Data.OldValue, Data.NewValue);
}

//回调定义 属性变化时广播对应委托 --- 暴击率
void AMyCharacterBase::OnCriticalChanceChanged(const FOnAttributeChangeData& Data)
{
	if (Data.OldValue == Data.NewValue)
	{
		return;
	}
	CriticalChanceChangedEvent.Broadcast(Data.OldValue, Data.NewValue);
}

//回调定义 属性变化时广播对应委托 --- 暴击伤害倍率
void AMyCharacterBase::OnCriticalMultiplierChanged(const FOnAttributeChangeData& Data)
{
	if (Data.OldValue == Data.NewValue)
	{
		return;
	}
	CriticalMultiplierChangedEvent.Broadcast(Data.OldValue, Data.NewValue);
}

//回调定义 属性变化时广播对应委托 --- 穿透等级
void AMyCharacterBase::OnPenetrationLevelChanged(const FOnAttributeChangeData& Data)
{
	if (Data.OldValue == Data.NewValue)
	{
		return;
	}
	PenetrationLevelChangedEvent.Broadcast(Data.OldValue, Data.NewValue);
}

//回调定义 属性变化时广播对应委托 --- 抛射物反弹次数
void AMyCharacterBase::OnProjectileBounceCountChanged(const FOnAttributeChangeData& Data)
{
	if (Data.OldValue == Data.NewValue)
	{
		return;
	}
	ProjectileBounceCountChangedEvent.Broadcast(Data.OldValue, Data.NewValue);
}

//回调定义 属性变化时广播对应委托 --- 技能冷却缩减
void AMyCharacterBase::OnSkillCooldownReductionChanged(const FOnAttributeChangeData& Data)
{
	if (Data.OldValue == Data.NewValue)
	{
		return;
	}
	SkillCooldownReductionChangedEvent.Broadcast(Data.OldValue, Data.NewValue);
}

//回调定义 属性变化时广播对应委托 --- 移动速度
void AMyCharacterBase::OnMoveSpeedChanged(const FOnAttributeChangeData& Data)
{
	if (Data.OldValue == Data.NewValue)
	{
		return;
	}
	MoveSpeedChangedEvent.Broadcast(Data.OldValue, Data.NewValue);
}

//回调定义 属性变化时广播对应委托 --- 子弹初速
void AMyCharacterBase::OnProjectileInitSpeedChanged(const FOnAttributeChangeData& Data)
{
	if (Data.OldValue == Data.NewValue)
	{
		return;
	}
	ProjectileInitSpeedChangedEvent.Broadcast(Data.OldValue, Data.NewValue);
}

//回调定义 属性变化时广播对应委托 --- 子弹初速
void AMyCharacterBase::OnAttackRangeChanged(const FOnAttributeChangeData& Data)
{
	if (Data.OldValue == Data.NewValue)
	{
		return;
	}
	AttackRangeChangedEvent.Broadcast(Data.OldValue, Data.NewValue);
}
