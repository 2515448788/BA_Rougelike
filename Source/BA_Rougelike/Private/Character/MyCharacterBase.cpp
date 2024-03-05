// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/MyCharacterBase.h"

// Sets default values
AMyCharacterBase::AMyCharacterBase()
{
	//实例化ASC
	EnhancedInputAbilitySystem = CreateDefaultSubobject<
		UEnhancedInputAbilitySystem>(TEXT("EnhancedInputAbilitySystem"));
}

UAbilitySystemComponent* AMyCharacterBase::GetAbilitySystemComponent() const
{
	return EnhancedInputAbilitySystem;
}
