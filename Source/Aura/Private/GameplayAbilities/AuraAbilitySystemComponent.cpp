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

void UAuraAbilitySystemComponent::AbilityInputTagHeld(const FGameplayTag& InputTag)
{
	if (!InputTag.IsValid())
		UE_LOG(LogTemp, Warning, TEXT("Held InputTag is not valid"));

	for (FGameplayAbilitySpec& Spec :  GetActivatableAbilities())
	{
		if (Spec.GetDynamicSpecSourceTags().HasTagExact(InputTag))
		{
			if (!Spec.IsActive())
			{
				//检索资源消耗与冷却等，尝试激活GA，成功返回true
				TryActivateAbility(Spec.Handle);
				
			}
			//通知GAS，该Spec的输入已被按下
			AbilitySpecInputPressed(Spec);
		}
	}
}

void UAuraAbilitySystemComponent::AbilityInputTagReleased(const FGameplayTag& InputTag)
{
	if (!InputTag.IsValid())
		UE_LOG(LogTemp, Warning, TEXT("Released InputTag is not valid"));

	for (FGameplayAbilitySpec& Spec :  GetActivatableAbilities())
	{
		if (Spec.GetDynamicSpecSourceTags().HasTagExact(InputTag))
		{
			if (Spec.IsActive())
			{
				//通知GAS，该Spec的输入已被释放
				AbilitySpecInputReleased(Spec);
			}
		}
	}
}

void UAuraAbilitySystemComponent::AddCharacterAbilities(const TArray<TSubclassOf<UAuraGameplayAbility>>& GameplayAbilities)
{
	for (const TSubclassOf<UAuraGameplayAbility>& Ability : GameplayAbilities)
	{
		FGameplayAbilitySpec AbilitySpec(Ability, 1); //需要修改，不能const

		//将初始Tag添加进动态容器，以便于后续修改
		UAuraGameplayAbility* AuraAbility = Cast<UAuraGameplayAbility>(AbilitySpec.Ability);
		if (AuraAbility && AuraAbility->StartupInputTag.IsValid())
		{
			AbilitySpec.GetDynamicSpecSourceTags().AddTag(AuraAbility->StartupInputTag);
		}
		
		GiveAbility(AbilitySpec);
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
  