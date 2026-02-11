// SiberianSledCat

#pragma once


#include "CoreMinimal.h"
#include "AuraWidgetController.h"
#include "AttributeMenuController.generated.h"

/**
 * 
 */

struct FGameplayTag;
struct FGameplayAttribute;
struct FAuraAttributeInfo;
class UAttributeInfo;

//重命名函数指针
typedef FGameplayAttribute (*FAttributeFuncPtr)();

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FAttributeInfoSignature, const FAuraAttributeInfo&, info);

/* 该类需要在蓝图中被创建并作为参数调用，前者可识别类型，后者可创建实例*/
UCLASS(BlueprintType, Blueprintable)
class AURA_API UAttributeMenuController : public UAuraWidgetController
{
	GENERATED_BODY()

public:
	/* 广播以初始化属性值，C++仅设置私有Value，文本与数值显示在BP Assign*/
	virtual void BroadcastInitializeValues() override;

	/* 绑定回调函数到依赖，在属性变更时修改显示的UI值*/
	virtual void BindCallbacksToDependencies() override;

protected:
	UPROPERTY(BlueprintAssignable)
	FAttributeInfoSignature OnMenuAttributeChanged;

	UPROPERTY(EditDefaultsOnly, Category = "GAS|Attributes")
	UAttributeInfo* AttributeInfo;

private:
	/* 根据Tag从AttributeInfo查找属性并从对应的函数指针中获取值后广播*/
	void BroadcastAttributeInfo(const FGameplayTag& GameplayTag, FAttributeFuncPtr GetAttributeFunction);
};
