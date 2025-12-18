// SiberianSledCat

#pragma once

#include "CoreMinimal.h"
#include "AuraWidgetController.h"
#include "OverlayWidgetController.generated.h"

/**
 * 
 */
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnHealthChangedSignatured, float, NewHewalth);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnMAXHealthChangedSignatured, float, NewMAXHewalth);

UCLASS(BlueprintType, Blueprintable)
class AURA_API UOverlayWidgetController : public UAuraWidgetController
{
	GENERATED_BODY()

protected:
	UPROPERTY(BlueprintAssignable, Category= "GAS|Attributes")
	FOnHealthChangedSignatured OnHealthChanged;

	UPROPERTY(BlueprintAssignable, Category= "GAS|Attributes")
	FOnMAXHealthChangedSignatured OnMAXHealthChanged;
public:
	virtual void BroadcastInitializeValues();
	
};
