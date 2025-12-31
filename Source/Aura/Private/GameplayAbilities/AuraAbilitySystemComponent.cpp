// SiberianSledCat


#include "GameplayAbilities/AuraAbilitySystemComponent.h"

void UAuraAbilitySystemComponent::AbilityActorInfoSet()
{
	OnGameplayEffectAppliedDelegateToSelf.AddUObject(this, &UAuraAbilitySystemComponent::EffectApplied);
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
  