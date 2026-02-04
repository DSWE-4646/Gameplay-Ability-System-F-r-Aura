// SiberianSledCat


#include "AuraGameplayTags.h"
#include "GameplayTagsManager.h"

FAuraGameplayTags FAuraGameplayTags::GameplayTags;
FGameplayTag FAuraGameplayTags::Attribute_Secondary_Armor;

FAuraGameplayTags::FAuraGameplayTags()
{
}

const FAuraGameplayTags& FAuraGameplayTags::Get()
{
	return GameplayTags;
}

void FAuraGameplayTags::InitializeGameplayTags()
{
	UGameplayTagsManager& TagManager = UGameplayTagsManager::Get();
	Attribute_Secondary_Armor = TagManager.AddNativeGameplayTag(FName("Attributes.Secondary.Armor"), FString("Reduces damage taken, improves block chance"));
}
