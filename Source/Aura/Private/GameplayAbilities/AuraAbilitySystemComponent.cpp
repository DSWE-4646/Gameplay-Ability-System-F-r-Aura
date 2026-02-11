// SiberianSledCat


#include "GameplayAbilities/AuraAbilitySystemComponent.h"
#include "GameplayAbilities/GameplayAbility/AuraGameplayAbility.h"
#include "AuraGameplayTags.h"

void UAuraAbilitySystemComponent::AbilityActorInfoSet()
{
	OnGameplayEffectAppliedDelegateToSelf.AddUObject(this, &UAuraAbilitySystemComponent::EffectApplied);

	/*测试是否注册了Native GameplayTag
	const FAuraGameplayTags& GameplayTags = FAuraGameplayTags::Get();
	const FGameplayTag ArmorTag = GameplayTags.Attributes_Secondary_Armor;
	if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(-1,
			3.f,
			FColor::MakeRandomColor(),
			FString::Printf(TEXT("ArmorTag: %s"), *ArmorTag.ToString()));
	}
	*/
}

void UAuraAbilitySystemComponent::AddCharacterAbilities(const TArray<TSubclassOf<UAuraGameplayAbility>>& GameplayAbilities)
{
	for (const TSubclassOf<UAuraGameplayAbility>& Ability : GameplayAbilities)
	{
		FGameplayAbilitySpec AbilitySpec(Ability, 1); //需要修改，不能const
		//GiveAbility(AbilitySpec);
		GiveAbilityAndActivateOnce(AbilitySpec);

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
  