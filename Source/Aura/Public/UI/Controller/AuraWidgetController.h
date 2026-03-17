// SiberianSledCat

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "AuraWidgetController.generated.h"


class UAttributeSet;
class UAbilitySystemComponent;
/**
 * 
 */
/* 用作传递参数的结构体*/

USTRUCT(BlueprintType)
struct FAuraWidgetControllerParams 
{
	GENERATED_BODY()

	/*提供默认构造函数与带参初始化列表2种方法*/
	FAuraWidgetControllerParams() {}
	FAuraWidgetControllerParams(UAbilitySystemComponent* ASCParam, APlayerController* PCParam, APlayerState* PSParam, UAttributeSet* ASParam)
		: ASCInWidCtlFS(ASCParam), PCInWidCtlFS(PCParam), PSInWidCtlFS(PSParam), ASInWidCtlFS(ASParam) {}
	
	UPROPERTY(BlueprintReadOnly, Category = "WidgetController")
	TObjectPtr<UAbilitySystemComponent> ASCInWidCtlFS = nullptr;

	UPROPERTY(BlueprintReadOnly, Category = "WidgetController")
	TObjectPtr<APlayerController> PCInWidCtlFS = nullptr;

	UPROPERTY(BlueprintReadOnly, Category = "WidgetController")
	TObjectPtr<APlayerState> PSInWidCtlFS = nullptr;

	UPROPERTY(BlueprintReadOnly, Category = "WidgetController")
	TObjectPtr<UAttributeSet> ASInWidCtlFS = nullptr;
};

UCLASS()
class AURA_API UAuraWidgetController : public UObject
{
	GENERATED_BODY()
public:
	/*使用传入的结构体初始化WidgetController*/
	UFUNCTION(BlueprintCallable)
	void SetWidgetControllerParams(const FAuraWidgetControllerParams& Params);

	/* 绑定Lambda到委托，在属性变化时广播，区别于初始化*/
	virtual void BindCallbacksToDependencies() {}
	
protected:
	UPROPERTY(BlueprintReadOnly, Category = "WidgetController")
	TObjectPtr<UAbilitySystemComponent> ASCInWidController;

	UPROPERTY(BlueprintReadOnly, Category = "WidgetController")
	TObjectPtr<APlayerController> PCInWidController;

	UPROPERTY(BlueprintReadOnly, Category = "WidgetController")
	TObjectPtr<APlayerState> PSInWidController;

	UPROPERTY(BlueprintReadOnly, Category = "WidgetController")
	TObjectPtr<UAttributeSet> ASInWidController;

	/* 在Health Mana MAX Health MAX Mana 发生变化时广播以初始化值*/
	UFUNCTION(BlueprintCallable)
	virtual void BroadcastInitializeValues();
};
