// SiberianSledCat


#include "UI/HUD/AuraHUD.h"

#include "Blueprint/UserWidget.h"
#include "UI/Widget/AuraUserWidget.h"
#include "UI/Controller/OverlayWidgetController.h"


UOverlayWidgetController* AAuraHUD::GetOverlayWidgetController(const FAuraWidgetControllerParams& FAWCtrlParams)
{
	if (OverlayWidCtlInHUD == nullptr)
	{
		OverlayWidCtlInHUD = NewObject<UOverlayWidgetController>(this, OverlayWidCtlInHUDSubclass);
		//OverlayWidCtlInHUD = NewObject<UOverlayWidgetController>();
		OverlayWidCtlInHUD ->SetWidgetControllerParams(FAWCtrlParams);
		return OverlayWidCtlInHUD;
	}
	return OverlayWidCtlInHUD;
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
