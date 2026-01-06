// SiberianSledCat

#pragma once

#include "CoreMinimal.h"
#include "AuraWidgetController.h"
#include "GameplayTagContainer.h"
#include "OverlayWidgetController.generated.h"

class UAuraUserWidget;
struct FOnAttributeChangeData;
class UUserWidget;
/**
 * 
 */
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnHealthChangedSignatured, float, NewHewalth);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnMAXHealthChangedSignatured, float, NewMAXHewalth);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnManaChangedSignature, float, NewMana);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnMAXManaChangedSignature, float, NewMaxMana);


USTRUCT(BlueprintType)
struct FUIWidgetRow : public FTableRowBase
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "UI Data")
	FGameplayTag MessageTag = FGameplayTag::EmptyTag;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "UI Data")
	FText MessageText = FText::GetEmpty();

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "UI Data")
	TSubclassOf<UAuraUserWidget> WidgetClass = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "UI Data")
	TObjectPtr<UTexture2D> icon = nullptr;
};

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FMessageWidgetRowSignature, const FUIWidgetRow&, Row);

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

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "UI Data")
	TObjectPtr<UDataTable> MessageWidgetDataTable = nullptr;

	template<typename T>
	T* GetDataTableRowbyTag(const UDataTable* DataTable, const FGameplayTag& Tag)
	{
		T* Row = DataTable->FindRow<T>(Tag.GetTagName(), "");
		return Row;
	}

	UPROPERTY(BlueprintAssignable, Category= "GAS|Attributes")
	FMessageWidgetRowSignature MessageWidgetRowSignature;
	
public:
	virtual void BroadcastInitializeValues() override;
	virtual void BindCallbacksToDependencies() override;

	
	
};


