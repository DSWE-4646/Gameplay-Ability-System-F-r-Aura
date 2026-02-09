// SiberianSledCat

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "Engine/DataAsset.h"
#include "AttributeInfo.generated.h"

/**
 * 
 */

USTRUCT(BlueprintType)
struct FAuraAttributeInfo
{
	GENERATED_BODY()

	/* 用于标识属性的GameplayTag */
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly)
	FGameplayTag AttributeTag;

	/* 用户界面文本显示的名称 */
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly)
	FText DisplayName;

	/* 属性描述文本 */
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly)
	FText Description;

	/* 属性当前数值（仅蓝图可读，不暴露给数据资产编辑） */
	UPROPERTY(BlueprintReadOnly)
	float AttributeValue = 0.f;
};

UCLASS()
class AURA_API UAttributeInfo : public UDataAsset
{
	GENERATED_BODY()
public:
	/* 在属性信息数组中查找指定Tag对应的信息，如果找到则返回对应的信息，否则返回空信息*/
	UFUNCTION(BlueprintCallable)
	FAuraAttributeInfo FindAttributeInfo(const FGameplayTag& AttributeTag, bool bFound = false) const;
	
protected:
	/* 属性信息数组 */
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly)
	TArray<FAuraAttributeInfo> AttributeInformation;
	
};
