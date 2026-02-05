// SiberianSledCat


#include "AuraGameplayTags.h"
#include "GameplayTagsManager.h"

FAuraGameplayTags FAuraGameplayTags::GameplayTags; //实现静态成员变量，类型 作用域::静态成员变量

const FAuraGameplayTags& FAuraGameplayTags::Get()
{
	return GameplayTags;
}

void FAuraGameplayTags::InitializeGameplayTags()
{
	UGameplayTagsManager& TagManager = UGameplayTagsManager::Get();

	// ==============================================
    // 主属性 Native Tag 注册
    // ==============================================
    GameplayTags.Attributes_Primary_Strength = TagManager.AddNativeGameplayTag(
        FName("Attributes.Primary.Strength"),
        FString("Increases physical damage")
    );
GameplayTags.Attributes_Primary_Intelligence = TagManager.AddNativeGameplayTag(
        FName("Attributes.Primary.Intelligence"),
        FString("Increases magical damage")
    );
GameplayTags.Attributes_Primary_Resilience = TagManager.AddNativeGameplayTag(
        FName("Attributes.Primary.Resilience"),
        FString("Increases armor and armor penetration")
    );
GameplayTags.Attributes_Primary_Vigor = TagManager.AddNativeGameplayTag(
        FName("Attributes.Primary.Vigor"),
        FString("Increases health")
    );

    // ==============================================
    // 副属性 Native Tag 注册
    // ==============================================
    GameplayTags.Attributes_Secondary_Armor = TagManager.AddNativeGameplayTag(
        FName("Attributes.Secondary.Armor"),
        FString("Reduces damage taken, improves block chance")
    );
GameplayTags.Attributes_Secondary_ArmorPenetration = TagManager.AddNativeGameplayTag(
        FName("Attributes.Secondary.ArmorPenetration"),
        FString("Ignores a percentage of enemy armor")
    );
GameplayTags.Attributes_Secondary_BlockChance = TagManager.AddNativeGameplayTag(
        FName("Attributes.Secondary.BlockChance"),
        FString("Chance to block incoming physical damage")
    );
GameplayTags.Attributes_Secondary_CriticalHitChance = TagManager.AddNativeGameplayTag(
        FName("Attributes.Secondary.CriticalHitChance"),
        FString("Chance to deal critical damage")
    );
GameplayTags.Attributes_Secondary_CriticalHitDamage = TagManager.AddNativeGameplayTag(
        FName("Attributes.Secondary.CriticalHitDamage"),
        FString("Bonus damage dealt on critical hits")
    );
GameplayTags.Attributes_Secondary_CriticalHitResistance = TagManager.AddNativeGameplayTag(
        FName("Attributes.Secondary.CriticalHitResistance"),
        FString("Reduces critical hit chance taken")
    );
GameplayTags.Attributes_Secondary_HealthRegeneration = TagManager.AddNativeGameplayTag(
        FName("Attributes.Secondary.HealthRegeneration"),
        FString("Restores health over time")
    );
GameplayTags.Attributes_Secondary_ManaRegeneration = TagManager.AddNativeGameplayTag(
        FName("Attributes.Secondary.ManaRegeneration"),
        FString("Restores mana over time")
    );
GameplayTags.Attributes_Secondary_MaxHealth = TagManager.AddNativeGameplayTag(
        FName("Attributes.Secondary.MaxHealth"),
        FString("Maximum health capacity")
    );
GameplayTags.Attributes_Secondary_MaxMana = TagManager.AddNativeGameplayTag(
        FName("Attributes.Secondary.MaxMana"),
        FString("Maximum mana capacity")
    );

}
