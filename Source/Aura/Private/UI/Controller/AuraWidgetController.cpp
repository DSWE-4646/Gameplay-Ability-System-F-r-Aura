// SiberianSledCat


#include "UI/Controller/AuraWidgetController.h"

void UAuraWidgetController::SetWidgetControllerParams(const FAuraWidgetControllerParams& Params)
{
	ASCInWidController = Params.ASCInWidCtlFS;
	PCInWidController = Params.PCInWidCtlFS;
	PSInWidController = Params.PSInWidCtlFS;
	ASInWidController = Params.ASInWidCtlFS;
}

void UAuraWidgetController::BroadcastInitializeValues()
{
}
