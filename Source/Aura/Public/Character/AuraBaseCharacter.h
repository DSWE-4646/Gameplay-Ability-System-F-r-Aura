// SiberianSledCat

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "AbilitySystemInterface.h"
#include "Interface/CombatInterface.h"
#include "AuraBaseCharacter.generated.h"

class UGameplayEffect;
class UAttributeSet;
class UAbilitySystemComponent;


UCLASS(Abstract, meta = (DisableNativeTick))
class AURA_API AAuraBaseCharacter : public ACharacter, public IAbilitySystemInterface , public ICombatInterface
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

	virtual void InitAbilityActorInfoInCharac();

	/* 用于初始化角色的GE类 */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Attributes")
	TSubclassOf<UGameplayEffect> DefaultPrimaryAttributeGE;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Attributes")
	TSubclassOf<UGameplayEffect> SecondaryAttributeGE;

	/* 调用GE初始化角色的AS by 调用ApplyGEToSelfForInit */
	void InitDefaultAttributes() const;

	/* 调用传入的GE初始化角色的主要AS，并启用无限的附属GE以在其他AS更新时修改计算值 */
	void ApplyGEToSelfForInit(TSubclassOf<UGameplayEffect> GEClass, float Level = 1.f) const;
};
