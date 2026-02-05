// SiberianSledCat


#include "GameplayAbilities/AuraAbilitySystemComponent.h"

#include "AuraGameplayTags.h"

void UAuraAbilitySystemComponent::AbilityActorInfoSet()
{
	OnGameplayEffectAppliedDelegateToSelf.AddUObject(this, &UAuraAbilitySystemComponent::EffectApplied);

	const FAuraGameplayTags& GameplayTags = FAuraGameplayTags::Get();
	const FGameplayTag ArmorTag = GameplayTags.Attributes_Secondary_Armor;
	if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(-1,
			3.f,
			FColor::MakeRandomColor(),
			FString::Printf(TEXT("ArmorTag: %s"), *ArmorTag.ToString()));
	}
}

void UAuraAbilitySystemComponent::EffectApplied(UAbilitySystemComponent* ASC,
	const FGameplayEffectSpec& EffectSpec,
	FActiveGameplayEffectHandle ActiveGameplayEffectHandle)
{
	//GEngine->AddOnScreenDebugMessage(-1, 3.f, FColor::MakeRandomColor(), TEXT("EffectApplied"));
	FGameplayTagContainer TagsContainer;
	EffectSpec.GetAllAssetTags(TagsContainer);

	EffectAssetTags.Broadcast(TagsContainer);
	
}
  