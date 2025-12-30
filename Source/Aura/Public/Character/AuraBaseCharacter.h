// SiberianSledCat

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "AbilitySystemInterface.h"
#include "AuraBaseCharacter.generated.h"

class UAttributeSet;
class UAbilitySystemComponent;


UCLASS(Abstract, meta = (DisableNativeTick))
class AURA_API AAuraBaseCharacter : public ACharacter, public IAbilitySystemInterface 
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AAuraBaseCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	UPROPERTY(EditAnywhere)
	TObjectPtr<USkeletalMeshComponent> Weapon;

	UPROPERTY()
	TObjectPtr<UAbilitySystemComponent> AbilitySystemInCharac;
	UPROPERTY()
	TObjectPtr<UAttributeSet> AttributeSetInCharac;

	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;
	virtual UAttributeSet* GetAttributeSet() const;

	virtual void InitAbilityActorInfoInAuraCharac();
private:
	
};
