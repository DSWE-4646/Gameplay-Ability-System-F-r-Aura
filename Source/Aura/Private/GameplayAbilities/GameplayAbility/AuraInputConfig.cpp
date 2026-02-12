// SiberianSledCat


#include "GameplayAbilities/GameplayAbility/AuraInputConfig.h"

UInputAction* UAuraInputConfig::FindAbilityInputActionByTag(const FGameplayTag& GameplayTag, bool bLogNotFound) const
{
	if (InputActions.IsEmpty() && !GameplayTag.IsValid())
	{
		for (auto& Action : InputActions)
		{
			if (Action.InputAction && GameplayTag == Action.ActionTag)
			return Action.InputAction;
		}
	}

	if (bLogNotFound)
	{
		UE_LOG(LogTemp, Error, TEXT("Can't find AbilityInputAction for InputTag [%s] on InputConfig [%s]"), *GameplayTag.ToString(), *GetNameSafe(this));
	}
	return nullptr;
}
