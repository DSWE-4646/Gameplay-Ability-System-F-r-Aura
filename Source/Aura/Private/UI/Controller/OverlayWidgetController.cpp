// SiberianSledCat


#include "UI/Controller/OverlayWidgetController.h"

#include "GameplayAbilities/AuraAttributeSet.h"

void UOverlayWidgetController::BroadcastInitializeValues()
{
	const UAuraAttributeSet* ASInOverlayCtrl = Cast<UAuraAttributeSet>(ASInWidController);
	OnHealthChanged.Broadcast(ASInOverlayCtrl->GetHealth());
	OnMAXHealthChanged.Broadcast(ASInOverlayCtrl->GetMaxHealth());
}
