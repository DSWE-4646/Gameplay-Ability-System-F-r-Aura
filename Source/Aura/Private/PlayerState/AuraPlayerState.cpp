// SiberianSledCat


#include "PlayerState/AuraPlayerState.h"

#include "GameplayAbilities/AuraAbilitySystemComponent.h"
#include "GameplayAbilities/AuraAttributeSet.h"

AAuraPlayerState::AAuraPlayerState()
{
	SetNetUpdateFrequency(100.f);

	AbilitiesSystemInPlayerState = CreateDefaultSubobject<UAuraAbilitySystemComponent>("ASCInPlayerState");
	AbilitiesSystemInPlayerState->SetIsReplicated(true);

	AttributeSetInPlayerState = CreateDefaultSubobject<UAuraAttributeSet>("ASCInPlayerState");
}
