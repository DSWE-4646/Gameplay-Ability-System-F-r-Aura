// SiberianSledCat


#include "UI/Widget/AuraUserWidget.h"

void UAuraUserWidget::SetWidgetController(UObject* WigController)
{
	WidgetController = WigController;
	BoundWidgetController();
}
