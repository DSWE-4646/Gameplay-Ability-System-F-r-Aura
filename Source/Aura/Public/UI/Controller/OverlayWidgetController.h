// SiberianSledCat

#pragma once

#include "CoreMinimal.h"
#include "AuraWidgetController.h"
#include "OverlayWidgetController.generated.h"

struct FOnAttributeChangeData;
/**
 * 
 */
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnHealthChangedSignatured, float, NewHewalth);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnMAXHealthChangedSignatured, float, NewMAXHewalth);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnManaChangedSignature, float, NewMana);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnMAXManaChangedSignature, float, NewMaxMana);


UCLASS(BlueprintType, Blueprintable)
class AURA_API UOverlayWidgetController : public UAuraWidgetController
{
	GENERATED_BODY()

protected:
	UPROPERTY(BlueprintAssignable, Category= "GAS|Attributes")
	FOnHealthChangedSignatured OnHealthChanged;

	UPROPERTY(BlueprintAssignable, Category= "GAS|Attributes")
	FOnMAXHealthChangedSignatured OnMAXHealthChanged;

	UPROPERTY(BlueprintAssignable, Category= "GAS|Attributes")
	FOnManaChangedSignature OnManaChanged;

	UPROPERTY(BlueprintAssignable, Category= "GAS|Attributes")
	FOnMAXManaChangedSignature OnMAXManaChanged;
	
	void HealthChanged(const FOnAttributeChangeData& Data) const;
	void MAXHealthChanged(const FOnAttributeChangeData& Data) const;

	void ManaChanged(const FOnAttributeChangeData& Data) const;
	void MAXManaChanged(const FOnAttributeChangeData& Data) const;
	
public:
	virtual void BroadcastInitializeValues() override;
	virtual void BindCallbacksToDependencies() override;
	
};
