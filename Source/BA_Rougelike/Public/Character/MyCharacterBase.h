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
	//ASC组件
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "EnhancedAbilitySystem")
	UEnhancedInputAbilitySystem* EnhancedInputAbilitySystem;
	//接口函数 获取ASC
	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;
};
