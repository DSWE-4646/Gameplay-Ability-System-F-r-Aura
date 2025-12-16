// SiberianSledCat


#include "UI/HUD/AuraHUD.h"

#include "Blueprint/UserWidget.h"
#include "UI/Widget/AuraUserWidget.h"

void AAuraHUD::BeginPlay()
{
	Super::BeginPlay();

	if (!OverlayWidgetClass || !GetWorld())
		return;
	
	DisplayWidget = CreateWidget<UAuraUserWidget>(GetWorld(),  OverlayWidgetClass);
	
	if (DisplayWidget)
	DisplayWidget->AddToViewport();
}
