// SiberianSledCat

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "AuraHUD.generated.h"

class UAttributeMenuController;
class UAbilitySystemComponent;
class UAttributeSet;
struct FAuraWidgetControllerParams;
class UOverlayWidgetController;
class UAuraUserWidget;
/**
 * 
 */
UCLASS()
class AURA_API AAuraHUD : public AHUD
{
	GENERATED_BODY()

public:
	/* 将被蓝图函数库调用 */
	UOverlayWidgetController* GetOverlayWidgetController(const FAuraWidgetControllerParams& FAWCtrlParams);
	UAttributeMenuController* GetAttributeMenuController(const FAuraWidgetControllerParams& FAWCtrlParams);

	void InitializeOverlayWidget(UAbilitySystemComponent* ASCParam, APlayerController* PCParam, APlayerState* PSParam, UAttributeSet* ASParam);
protected:
	//将被显示的控件类
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UAuraUserWidget> OverlayWidgetClass;

	//用于指定将创建的AttributeMenuController类
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UAttributeMenuController> AttributeMenuControllerClass;

	//用于指定将创建的OverlayWidgetController类
	UPROPERTY(EditAnywhere)
	TSubclassOf<UOverlayWidgetController> OverlayWidCtlInHUDSubclass;

private:
	/* 此处的类由程序初始化，不应被赋值 */
	
	//指向创建出的AttributeMenuController
	UPROPERTY()
	TObjectPtr<UAttributeMenuController> AttributeMenuController = nullptr;

	//指向创建出的将被显示控件
	UPROPERTY()
	TObjectPtr<UAuraUserWidget> DisplayWidget;

	//指向创建出的OverlayWidgetController
	UPROPERTY()
	TObjectPtr<UOverlayWidgetController> OverlayWidCtlInHUD  = nullptr;
};
