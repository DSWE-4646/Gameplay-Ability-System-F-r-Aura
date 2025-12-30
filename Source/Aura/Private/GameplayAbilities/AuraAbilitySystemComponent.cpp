// SiberianSledCat


#include "GameplayAbilities/AuraAbilitySystemComponent.h"

void UAuraAbilitySystemComponent::AbilityActorInfoSet()
{
	OnGameplayEffectAppliedDelegateToSelf.AddUObject(this, &UAuraAbilitySystemComponent::EffectApplied);
}

void UAuraAbilitySystemComponent::EffectApplied(UAbilitySystemComponent*,
	const FGameplayEffectSpec&,
	FActiveGameplayEffectHandle)
{
	GEngine->AddOnScreenDebugMessage(-1, 3.f, FColor::MakeRandomColor(), TEXT("EffectApplied"));
}
