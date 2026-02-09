// SiberianSledCat


#include "GameplayAbilities/AuraAbilitySystemLibrary.h"
#include "GameplayAbilities/AuraAttributeSet.h"
#include "Kismet/GameplayStatics.h"
#include "PlayerState/AuraPlayerState.h"
#include "UI/Controller/AuraWidgetController.h"
#include "UI/HUD/AuraHUD.h"

UOverlayWidgetController* UAuraAbilitySystemLibrary::GetOverlayWidgetController(const UObject* WorldContextObject)
{
	if (APlayerController* PC = UGameplayStatics::GetPlayerController(WorldContextObject, 0))
	{
		if (AAuraHUD* AuraHUD = PC->GetHUD<AAuraHUD>())
		{
			AAuraPlayerState* PSParam = PC->GetPlayerState<AAuraPlayerState>();
			UAbilitySystemComponent* ASCParam = PSParam->GetAbilitySystemComponent();
			UAttributeSet* ASParam = PSParam->GetAttributeSet();
			const FAuraWidgetControllerParams Params(ASCParam, PC, PSParam, ASParam);
			return AuraHUD->GetOverlayWidgetController(Params);
		}
	}

	return nullptr;
}
