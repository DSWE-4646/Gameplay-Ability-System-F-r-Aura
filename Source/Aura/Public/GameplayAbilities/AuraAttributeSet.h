// SiberianSledCat

#pragma once

#include "CoreMinimal.h"
#include "AttributeSet.h"
#include "GameplayAbilities/AuraAbilitySystemComponent.h"
#include "AuraAttributeSet.generated.h"


/**
 * 
 */

#define ATTRIBUTE_ACCESSORS(ClassName, PropertyName) \
GAMEPLAYATTRIBUTE_PROPERTY_GETTER(ClassName, PropertyName) \
GAMEPLAYATTRIBUTE_VALUE_GETTER(PropertyName) \
GAMEPLAYATTRIBUTE_VALUE_SETTER(PropertyName) \
GAMEPLAYATTRIBUTE_VALUE_INITTER(PropertyName)

//用于存储GE来源与目标的ASC、AvatarActor、Controller、Character的struct
USTRUCT()
struct FEffectProperties
{
	GENERATED_BODY()
	FEffectProperties() //FGameplayEffectContextHandle有自己的默认构造函数无需此处手动初始化
		: SourceASC(nullptr)
		,SourceAvatarActor(nullptr)
		, SourceController(nullptr)
		,SourceCharacter(nullptr)
		,TargetASC(nullptr)
		,TargetAvatarActor(nullptr)
		,TargetController(nullptr)
		,TargetCharacter(nullptr)
	{}

	FGameplayEffectContextHandle FGameplayEffectContextHandle; //从PostGameplayEffectExecute传入的的Data获取
	
	UPROPERTY()
	UAbilitySystemComponent* SourceASC; //从FGameplayEffectContextHandle获取

	UPROPERTY()
	AActor* SourceAvatarActor; //从ASC的AbilityActorInfo->AvatarActor.get获取

	UPROPERTY()
	AController* SourceController; //从AvatarActor Cast的APawn指针获取

	UPROPERTY()
	ACharacter* SourceCharacter; //从Props.SourceAvatarActor Cast过来的

	UPROPERTY()
	UAbilitySystemComponent* TargetASC; //FGameplayEffectModCallbackData&的target就是一个ASC，此处也用AS蓝图库获取ASC

	UPROPERTY()
	AActor* TargetAvatarActor; //从ASC的AbilityActorInfo->AvatarActor.get获取

	UPROPERTY()
	AController* TargetController; //从AvatarActor Cast的APawn指针获取

	UPROPERTY()
	ACharacter* TargetCharacter; //从Props.TargetAvatarActor Cast过来的
};

UCLASS()
class AURA_API UAuraAttributeSet : public UAttributeSet
{
	GENERATED_BODY()
	
	UAuraAttributeSet();
public:
	/* 生成基础属性的属性访问器函数 */
	ATTRIBUTE_ACCESSORS(UAuraAttributeSet, Health)
	ATTRIBUTE_ACCESSORS(UAuraAttributeSet, MaxHealth)
	ATTRIBUTE_ACCESSORS(UAuraAttributeSet, Mana)
	ATTRIBUTE_ACCESSORS(UAuraAttributeSet, MaxMana)

	/* 生成加点属性的属性访问器函数 */
	ATTRIBUTE_ACCESSORS(UAuraAttributeSet, Strength)
	ATTRIBUTE_ACCESSORS(UAuraAttributeSet, Intelligence)
	ATTRIBUTE_ACCESSORS(UAuraAttributeSet, Resilience)
	ATTRIBUTE_ACCESSORS(UAuraAttributeSet, Vigor)

protected:

	/* 基础数据 */
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing= OnRep_Health, Category = "Vital Attributes")
	FGameplayAttributeData     Health;
	
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing= OnRep_MaxHealth, Category = "Vital Attributes")
	FGameplayAttributeData     MaxHealth;
	
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing= OnRep_Mana, Category = "Vital Attributes")
	FGameplayAttributeData     Mana;
	
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing= OnRep_MaxMana, Category = "Vital Attributes")
	FGameplayAttributeData     MaxMana;

	/*加点属性*/
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing= OnRep_Strength, Category = "primary Attributes")
	FGameplayAttributeData     Strength;

	UPROPERTY(BlueprintReadOnly, ReplicatedUsing= OnRep_Intelligence, Category = "primary Attributes")
	FGameplayAttributeData     Intelligence;

	UPROPERTY(BlueprintReadOnly, ReplicatedUsing= OnRep_Resilience, Category = "primary Attributes")
	FGameplayAttributeData	   Resilience;
	
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing= OnRep_Vigor, Category = "primary Attributes")
	FGameplayAttributeData     Vigor;

	
	/* 调用SetEffectProperties获取GE上下文与核心信息并存储，
	 * 还被用于在应用GE后钳制AS值更新快照，确保持续/状态GE的计算值与AS值相一致 */
	virtual void PostGameplayEffectExecute(const struct FGameplayEffectModCallbackData& Data) override;

	
private:
	/* 在网络宏注册AS的属性，使这些AS值在网络同步时被复制 */
	virtual void GetLifetimeReplicatedProps(TArray<class FLifetimeProperty>& OutLifetimeProps) const override;
	
	/* 加点属性的OnRep函数，用于在属性值改变时更新AS值,内部函数通知GAS系统更新AS值、GE快照并触发OnAttributeChange */
	UFUNCTION()
	void OnRep_Strength(const FGameplayAttributeData& OldStrength) const;
	
	UFUNCTION()
	void OnRep_Intelligence(const FGameplayAttributeData& OldIntelligence) const;

	UFUNCTION()
	void OnRep_Resilience(const FGameplayAttributeData& OldResilience) const;

	UFUNCTION()
	void OnRep_Vigor(const FGameplayAttributeData& OldVigor) const;

	/* 基础属性的OnRep函数，用于在属性值改变时更新AS值 */
	UFUNCTION()
	void OnRep_Health(const FGameplayAttributeData& OldHealth) const;

	UFUNCTION()
	void OnRep_MaxHealth(const FGameplayAttributeData& OldMaxHealth) const;

	UFUNCTION()
	void OnRep_Mana(const FGameplayAttributeData& OldMana) const;

	UFUNCTION()
	void OnRep_MaxMana(const FGameplayAttributeData& OldMaxMana) const;

	/* 钳制对于属性值的修改，确保设置的新值在有效范围内，注意此时GE已经创建快照，
	 * 对于持续/状态GE，由于他们计算采用的的是快照，
	 * 可能导致计算值与AS值相矛盾，需要在 PostGameplayEffectExecute中Setter AS*/
	virtual void PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue) override;

	/* 用于在PostGameplayEffectExecute中获取一些属性并存储在传入的Props中 */
	void SetEffectProperties(const FGameplayEffectModCallbackData& Data, FEffectProperties& Props) const;
};
