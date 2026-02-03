// SiberianSledCat


#include "AuraGameplayTags.h"
#include "GameplayTagsManager.h"

FAuraGameplayTags FAuraGameplayTags::GameplayTags;

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
	TagManager.AddNativeGameplayTag(FName("Attributes.Secondary.Armor"), FString("Reduces damage taken, improves block chance"));
}
