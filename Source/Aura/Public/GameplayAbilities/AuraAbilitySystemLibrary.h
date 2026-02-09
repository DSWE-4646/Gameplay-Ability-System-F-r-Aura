// SiberianSledCat

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "AuraAbilitySystemLibrary.generated.h"

class UAttributeMenuController;
class UOverlayWidgetController;
/**
 * 
 */
UCLASS()
class AURA_API UAuraAbilitySystemLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
	/* 该类并不会实例化，因此使用static访问函数，由于不一定存在于世界中，需要上下文来访问世界中的对象*/
	/* 调用AuraHUD类的获取函数来解耦*/
	UFUNCTION(BlueprintPure, Category = "Aura Ability System Library|Widget Controller")
	static UOverlayWidgetController* GetOverlayWidgetController(const UObject* WorldContextObject);

	/* 调用AuraHUD类的获取函数来解耦*/
	UFUNCTION(BlueprintPure, Category = "Aura Ability System Library|Widget Controller")
	static UAttributeMenuController* GetAttributeMenuController(const UObject* WorldContextObject);
};
