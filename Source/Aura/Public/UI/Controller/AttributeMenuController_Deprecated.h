// SiberianSledCat

#pragma once

#include "CoreMinimal.h"
#include "AuraWidgetController.h"
#include "AttributeMenuController_Deprecated.generated.h"

/**
 * 
 */
UCLASS()
class AURA_API UAttributeMenuController_Deprecated : public UAuraWidgetController
{
	GENERATED_BODY()

public:
	/**/
	virtual void BroadcastInitializeValues() override;

	/**/
	virtual void BindCallbacksToDependencies() override;
};
