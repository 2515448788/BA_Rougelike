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
		FOnGameplayAttributeValueChange& AttackIntervalChangeDelegate = EnhancedInputAbilitySystem->
			GetGameplayAttributeValueChangeDelegate(UMyAttributeSet_Character::GetAttackIntervalAttribute());
		AttackIntervalChangeDelegate.AddUObject(this, &AMyCharacterBase::OnAttackIntervalChanged);
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
		//获取ASC组件里对应属性变化的委托并绑定自己定义的回调---当前弹匣容量
		FOnGameplayAttributeValueChange& MagazineSizeChangeDelegate = EnhancedInputAbilitySystem->
			GetGameplayAttributeValueChangeDelegate(UMyAttributeSet_Character::GetMagazineSizeAttribute());
		MagazineSizeChangeDelegate.AddUObject(this, &AMyCharacterBase::OnMagazineSizeChanged);
		//获取ASC组件里对应属性变化的委托并绑定自己定义的回调---最大弹匣容量
		FOnGameplayAttributeValueChange& MaxMagazineSizeChangeDelegate = EnhancedInputAbilitySystem->
			GetGameplayAttributeValueChangeDelegate(UMyAttributeSet_Character::GetMaxMagazineSizeAttribute());
		MaxMagazineSizeChangeDelegate.AddUObject(this, &AMyCharacterBase::OnMaxMagazineSizeChanged);
		//获取ASC组件里对应属性变化的委托并绑定自己定义的回调---移动速度
		FOnGameplayAttributeValueChange& MoveSpeedChangeDelegate = EnhancedInputAbilitySystem->
			GetGameplayAttributeValueChangeDelegate(UMyAttributeSet_Character::GetMoveSpeedAttribute());
		MoveSpeedChangeDelegate.AddUObject(this, &AMyCharacterBase::OnMoveSpeedChanged);
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
	HealthChangedEvent.Broadcast(Data.NewValue);
}

//回调定义 属性变化时广播对应委托 --- 最大血量
void AMyCharacterBase::OnMaxHealthChanged(const FOnAttributeChangeData& Data)
{
	MaxHealthChangedEvent.Broadcast(Data.NewValue);
}

//回调定义 属性变化时广播对应委托 --- 血量再生
void AMyCharacterBase::OnHealthRegenerationChanged(const FOnAttributeChangeData& Data)
{
	HealthRegenerationChangedEvent.Broadcast(Data.NewValue);
}

//回调定义 属性变化时广播对应委托 --- 等级
void AMyCharacterBase::OnLevelChanged(const FOnAttributeChangeData& Data)
{
	LevelChangedEvent.Broadcast(Data.NewValue);
}

//回调定义 属性变化时广播对应委托 --- 经验值
void AMyCharacterBase::OnEXPChanged(const FOnAttributeChangeData& Data)
{
	EXPChangedEvent.Broadcast(Data.NewValue);
}

//回调定义 属性变化时广播对应委托 --- 最大经验值
void AMyCharacterBase::OnMaxEXPChanged(const FOnAttributeChangeData& Data)
{
	MaxEXPChangedEvent.Broadcast(Data.NewValue);
}

//回调定义 属性变化时广播对应委托 --- 拾取半径
void AMyCharacterBase::OnPickupRadiusChanged(const FOnAttributeChangeData& Data)
{
	PickupRadiusChangedEvent.Broadcast(Data.NewValue);
}

//回调定义 属性变化时广播对应委托 --- 经验倍率
void AMyCharacterBase::OnEXPMultiplierChanged(const FOnAttributeChangeData& Data)
{
	EXPMultiplierChangedEvent.Broadcast(Data.NewValue);
}

//回调定义 属性变化时广播对应委托 --- 护盾值
void AMyCharacterBase::OnEnergyShieldChanged(const FOnAttributeChangeData& Data)
{
	EnergyShieldChangedEvent.Broadcast(Data.NewValue);
}

//回调定义 属性变化时广播对应委托 --- 最大护盾值
void AMyCharacterBase::OnMaxEnergyShieldChanged(const FOnAttributeChangeData& Data)
{
	MaxEnergyShieldChangedEvent.Broadcast(Data.NewValue);
}

//回调定义 属性变化时广播对应委托 --- 护盾值再生
void AMyCharacterBase::OnEnergyShieldRegenerationChanged(const FOnAttributeChangeData& Data)
{
	EnergyShieldRegenerationChangedEvent.Broadcast(Data.NewValue);
}

//回调定义 属性变化时广播对应委托 --- 减伤率
void AMyCharacterBase::OnDamageReductionRateChanged(const FOnAttributeChangeData& Data)
{
	DamageReductionRateChangedEvent.Broadcast(Data.NewValue);
}

//回调定义 属性变化时广播对应委托 --- 闪避几率
void AMyCharacterBase::OnDodgeChanceChanged(const FOnAttributeChangeData& Data)
{
	DodgeChanceChangedEvent.Broadcast(Data.NewValue);
}

//回调定义 属性变化时广播对应委托 --- 最大闪避几率
void AMyCharacterBase::OnMaxDodgeChanceChanged(const FOnAttributeChangeData& Data)
{
	MaxDodgeChanceChangedEvent.Broadcast(Data.NewValue);
}

//回调定义 属性变化时广播对应委托 --- 攻击力
void AMyCharacterBase::OnAttackDamageChanged(const FOnAttributeChangeData& Data)
{
	AttackDamageChangedEvent.Broadcast(Data.NewValue);
}

//回调定义 属性变化时广播对应委托 --- 伤害倍率
void AMyCharacterBase::OnDamageMultiplierChanged(const FOnAttributeChangeData& Data)
{
	DamageMultiplierChangedEvent.Broadcast(Data.NewValue);
}

//回调定义 属性变化时广播对应委托 --- 攻击间隔
void AMyCharacterBase::OnAttackIntervalChanged(const FOnAttributeChangeData& Data)
{
	AttackIntervalChangedEvent.Broadcast(Data.NewValue);
}

//回调定义 属性变化时广播对应委托 --- 暴击率
void AMyCharacterBase::OnCriticalChanceChanged(const FOnAttributeChangeData& Data)
{
	CriticalChanceChangedEvent.Broadcast(Data.NewValue);
}

//回调定义 属性变化时广播对应委托 --- 暴击伤害倍率
void AMyCharacterBase::OnCriticalMultiplierChanged(const FOnAttributeChangeData& Data)
{
	CriticalMultiplierChangedEvent.Broadcast(Data.NewValue);
}

//回调定义 属性变化时广播对应委托 --- 穿透等级
void AMyCharacterBase::OnPenetrationLevelChanged(const FOnAttributeChangeData& Data)
{
	PenetrationLevelChangedEvent.Broadcast(Data.NewValue);
}

//回调定义 属性变化时广播对应委托 --- 抛射物反弹次数
void AMyCharacterBase::OnProjectileBounceCountChanged(const FOnAttributeChangeData& Data)
{
	ProjectileBounceCountChangedEvent.Broadcast(Data.NewValue);
}

//回调定义 属性变化时广播对应委托 --- 技能冷却缩减
void AMyCharacterBase::OnSkillCooldownReductionChanged(const FOnAttributeChangeData& Data)
{
	SkillCooldownReductionChangedEvent.Broadcast(Data.NewValue);
}

//回调定义 属性变化时广播对应委托 --- 当前弹匣容量
void AMyCharacterBase::OnMagazineSizeChanged(const FOnAttributeChangeData& Data)
{
	MagazineSizeChangedEvent.Broadcast(Data.NewValue);
}

//回调定义 属性变化时广播对应委托 --- 最大弹匣容量
void AMyCharacterBase::OnMaxMagazineSizeChanged(const FOnAttributeChangeData& Data)
{
	MaxMagazineSizeChangedEvent.Broadcast(Data.NewValue);
}

//回调定义 属性变化时广播对应委托 --- 移动速度
void AMyCharacterBase::OnMoveSpeedChanged(const FOnAttributeChangeData& Data)
{
	MoveSpeedChangedEvent.Broadcast(Data.NewValue);
}
