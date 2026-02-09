// SiberianSledCat

#pragma once

#include "CoreMinimal.h"
#include "AuraWidgetController.h"
#include "AttributeMenuController.generated.h"

/**
 * 
 */
/* 该类需要在蓝图中被创建并作为参数调用，前者可识别类型，后者可创建实例*/
UCLASS(BlueprintType, Blueprintable)
class AURA_API UAttributeMenuController : public UAuraWidgetController
{
	GENERATED_BODY()

public:
	/**/
	virtual void BroadcastInitializeValues() override;

	/**/
	virtual void BindCallbacksToDependencies() override;
};
