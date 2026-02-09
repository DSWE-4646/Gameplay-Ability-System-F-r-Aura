// SiberianSledCat

#pragma once


#include "CoreMinimal.h"
#include "AuraWidgetController.h"
#include "AttributeMenuController.generated.h"

/**
 * 
 */

struct FAuraAttributeInfo;
class UAttributeInfo;
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FAttributeInfoSignature, const FAuraAttributeInfo&, info);

/* 该类需要在蓝图中被创建并作为参数调用，前者可识别类型，后者可创建实例*/
UCLASS(BlueprintType, Blueprintable)
class AURA_API UAttributeMenuController : public UAuraWidgetController
{
	GENERATED_BODY()

public:
	/* 广播以初始化属性值，C++仅设置私有Value，文本与数值显示在BP Assign*/
	virtual void BroadcastInitializeValues() override;

	/**/
	virtual void BindCallbacksToDependencies() override;

protected:
	UPROPERTY(BlueprintAssignable)
	FAttributeInfoSignature OnMenuAttributeChanged;

	UPROPERTY(EditDefaultsOnly, Category = "GAS|Attributes")
	UAttributeInfo* AttributeInfo;

private:
	
};
