// SiberianSledCat

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemInterface.h"
#include "GameFramework/PlayerState.h"
#include "AuraPlayerState.generated.h"

class UAttributeSet;
class UAbilitySystemComponent;
/**
 * 
 */
UCLASS()
class AURA_API AAuraPlayerState : public APlayerState, public IAbilitySystemInterface
{
	GENERATED_BODY()

	AAuraPlayerState();

	UPROPERTY()
	TObjectPtr<UAbilitySystemComponent> AbilitiesSystemInPlayerState;
	UPROPERTY()
	TObjectPtr<UAttributeSet> AttributeSetInPlayerState;
};
