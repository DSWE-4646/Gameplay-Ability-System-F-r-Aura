// SiberianSledCat

#pragma once

#include "CoreMinimal.h"
#include "AuraWidgetController.h"
#include "AttributeMenuController.generated.h"

/**
 * 
 */
UCLASS()
class AURA_API UAttributeMenuController : public UAuraWidgetController
{
	GENERATED_BODY()

public:
	/**/
	virtual void BroadcastInitializeValues() override;

	/**/
	virtual void BindCallbacksToDependencies() override;
};
