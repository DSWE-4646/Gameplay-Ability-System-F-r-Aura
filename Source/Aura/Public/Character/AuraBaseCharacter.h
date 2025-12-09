// SiberianSledCat

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "AuraBaseCharacter.generated.h"
#include "AbilitySystemInterface.h"

class UAttributeSet;
class UAbilitySystemComponent;


UCLASS(Abstract, meta = (DisableNativeTick))
class AURA_API AAuraBaseCharacter : public ACharacter, public IAbilitySystemInterface //Rider居然没识别头文件？
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
	TObjectPtr<UAbilitySystemComponent> AbilitiesSystemInCharac;
	UPROPERTY()
	TObjectPtr<UAttributeSet> AttributeSetInCharac;

	
private:
	
};
