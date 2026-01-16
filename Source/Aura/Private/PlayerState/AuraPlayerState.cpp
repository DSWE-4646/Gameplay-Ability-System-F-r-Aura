// SiberianSledCat


#include "PlayerState/AuraPlayerState.h"

#include "GameplayAbilities/AuraAbilitySystemComponent.h"
#include "GameplayAbilities/AuraAttributeSet.h"
#include "Net/UnrealNetwork.h"

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

int32 AAuraPlayerState::GetPlayerLevel() const
{
	return PlayerLevel;
}

void AAuraPlayerState::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(AAuraPlayerState, PlayerLevel);
}

void AAuraPlayerState::OnRep_PlayerLevel(int32 OldLevel)
{
	
}


