// SiberianSledCat


#include "UI/Widget/AuraUserWidget.h"

void UAuraUserWidget::SetWidgetController(UObject* WigController)
{
	WidgetController = WigController;
	UE_LOG(LogTemp, Log, TEXT("SetWidgetController 被调用，准备触发 BoundWidgetController"));
	if (WidgetController)
		UE_LOG(LogTemp, Log, TEXT("WidgetController name is %s"), *WidgetController->GetName());
	BoundWidgetController();
}
