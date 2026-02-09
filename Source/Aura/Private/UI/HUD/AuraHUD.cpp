// SiberianSledCat


#include "UI/HUD/AuraHUD.h"

#include "Blueprint/UserWidget.h"
#include "UI/Widget/AuraUserWidget.h"
#include "UI/Controller/AttributeMenuController.h"
#include "UI/Controller/OverlayWidgetController.h"


UOverlayWidgetController* AAuraHUD::GetOverlayWidgetController(const FAuraWidgetControllerParams& FAWCtrlParams)
{
	// 如果没有初始化过，则初始化
	if (OverlayWidCtlInHUD == nullptr)
	{
		OverlayWidCtlInHUD = NewObject<UOverlayWidgetController>(this, OverlayWidCtlInHUDSubclass);
		//OverlayWidCtlInHUD = NewObject<UOverlayWidgetController>();
		OverlayWidCtlInHUD ->SetWidgetControllerParams(FAWCtrlParams);
		OverlayWidCtlInHUD ->BindCallbacksToDependencies();
	}
	return OverlayWidCtlInHUD;
}

UAttributeMenuController* AAuraHUD::GetAttributeMenuController(const FAuraWidgetControllerParams& FAWCtrlParams)
{
	// 如果没有初始化过，则初始化
	 if (AttributeMenuController == nullptr)
	    {
	        // 复用WidgetControllerParams创建实例
	        const FAuraWidgetControllerParams Params;
	       AttributeMenuController = NewObject<UAttributeMenuController>(this, AttributeMenuControllerClass);
	        AttributeMenuController->SetWidgetControllerParams(Params);
	        // 调用重写函数，完成初始化
	        AttributeMenuController->BindCallbacksToDependencies();
	        AttributeMenuController->BroadcastInitializeValues();
	    }
	    return AttributeMenuController;
}

void AAuraHUD::InitializeOverlayWidget(UAbilitySystemComponent* ASCParam, APlayerController* PCParam, APlayerState* PSParam, UAttributeSet* ASParam)
{
	checkf(OverlayWidgetClass, TEXT("Overlay Widget Class uninitialized, please finish it in BP child class!"));
	
	
	if (!OverlayWidgetClass || !GetWorld()) return;
	DisplayWidget = CreateWidget<UAuraUserWidget>(GetWorld(),  OverlayWidgetClass);

	const FAuraWidgetControllerParams WidgetControllerParams(ASCParam, PCParam, PSParam, ASParam);
	UOverlayWidgetController* OverlayWidgetController= GetOverlayWidgetController(WidgetControllerParams);

	checkf(OverlayWidCtlInHUD, TEXT("Overlay Widget Class Controller uninitialized, please finish it in BP child class!"))
	OverlayWidgetController->SetWidgetControllerParams(WidgetControllerParams);
	DisplayWidget->SetWidgetController(OverlayWidCtlInHUD);
	OverlayWidgetController->BroadcastInitializeValues();
	
	DisplayWidget->AddToViewport();
}
