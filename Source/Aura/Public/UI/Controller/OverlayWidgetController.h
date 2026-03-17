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
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnAttributeChangedSignatured, float, NewValue);

/* 作为数据表行模板，在编辑器继承蓝图创建数据表格用于 */
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
	FOnAttributeChangedSignatured OnHealthChanged;

	UPROPERTY(BlueprintAssignable, Category= "GAS|Attributes")
	FOnAttributeChangedSignatured OnMAXHealthChanged;

	UPROPERTY(BlueprintAssignable, Category= "GAS|Attributes")
	FOnAttributeChangedSignatured OnManaChanged;

	UPROPERTY(BlueprintAssignable, Category= "GAS|Attributes")
	FOnAttributeChangedSignatured OnMAXManaChanged;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "UI Data")
	TObjectPtr<UDataTable> MessageWidgetDataTable = nullptr;

	/* 模板函数，根据Tag返回数据表格中的指定类型*/
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


