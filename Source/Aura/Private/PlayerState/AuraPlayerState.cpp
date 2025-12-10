// SiberianSledCat


#include "PlayerState/AuraPlayerState.h"

#include "GameplayAbilities/AuraAbilitySystemComponent.h"
#include "GameplayAbilities/AuraAttributeSet.h"

AAuraPlayerState::AAuraPlayerState()
{
	SetNetUpdateFrequency(100.f);

	AbilitySystemInPlayerState = CreateDefaultSubobject<UAuraAbilitySystemComponent>("ASCInPlayerState");
	AbilitySystemInPlayerState->SetIsReplicated(true);
	AbilitySystemInPlayerState->SetReplicationMode(EGameplayEffectReplicationMode::Mixed);

	AttributeSetInPlayerState = CreateDefaultSubobject<UAuraAttributeSet>("AttributeSetInPlayerState");
}

UAbilitySystemComponent* AAuraPlayerState::GetAbilitySystemComponent() const
{
	return AbilitySystemInPlayerState;
}

UAttributeSet* AAuraPlayerState::GetAttributeSet() const
{
	return AttributeSetInPlayerState;
}


