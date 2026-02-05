// SiberianSledCat

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "AuraGameplayTags.generated.h"

USTRUCT()
struct FAuraGameplayTags
{
	GENERATED_BODY()
public:

	/* 返回FAuraGameplayTags的静态实例，这会初始化这个局部静态变量*/
	static const FAuraGameplayTags& Get();

	/* 将在AuraAssetManager中调用，用于在游戏开始时注册Attribute GameplayTags*/
	static void InitializeGameplayTags();
	
	// 主属性
	FGameplayTag Attributes_Primary_Strength;
	FGameplayTag Attributes_Primary_Intelligence;
	FGameplayTag Attributes_Primary_Resilience;
	FGameplayTag Attributes_Primary_Vigor;
	// 副属性
	FGameplayTag Attributes_Secondary_Armor;
	FGameplayTag Attributes_Secondary_ArmorPenetration;
	FGameplayTag Attributes_Secondary_BlockChance;
	FGameplayTag Attributes_Secondary_CriticalHitChance;
	FGameplayTag Attributes_Secondary_CriticalHitDamage;
	FGameplayTag Attributes_Secondary_CriticalHitResistance;
	FGameplayTag Attributes_Secondary_HealthRegeneration;
	FGameplayTag Attributes_Secondary_ManaRegeneration;
	FGameplayTag Attributes_Secondary_MaxHealth;
	FGameplayTag Attributes_Secondary_MaxMana;


protected:

private:
	static FAuraGameplayTags GameplayTags;

	//FAuraGameplayTags() = default;
	//FAuraGameplayTags(const FAuraGameplayTags&) = delete;
	//FAuraGameplayTags& operator=(const FAuraGameplayTags&) = delete;
	
};

