// SiberianSledCat


#include "UI/Controller/OverlayWidgetController.h"

#include "GameplayAbilities/AuraAttributeSet.h"



void UOverlayWidgetController::BindCallbacksToDependencies()
{
	if (!ASCInWidController || !ASInWidController) return;

	UAuraAttributeSet* AuraAS = Cast<UAuraAttributeSet>(ASInWidController);
	if (!AuraAS) return;
	ASCInWidController -> GetGameplayAttributeValueChangeDelegate(AuraAS->GetHealthAttribute()).AddUObject(this,
		&UOverlayWidgetController::HealthChanged);
	ASCInWidController -> GetGameplayAttributeValueChangeDelegate(AuraAS->GetMaxHealthAttribute()).AddUObject(this,
		&UOverlayWidgetController::MAXHealthChanged);
	ASCInWidController -> GetGameplayAttributeValueChangeDelegate(AuraAS->GetManaAttribute()).AddUObject(this,
		&UOverlayWidgetController::ManaChanged);
	ASCInWidController -> GetGameplayAttributeValueChangeDelegate(AuraAS->GetMaxManaAttribute()).AddUObject(this,
		&UOverlayWidgetController::MAXManaChanged);

	if (UAuraAbilitySystemComponent* AuraASC = Cast<UAuraAbilitySystemComponent>(ASCInWidController))
	{
		AuraASC->EffectAssetTags.AddLambda([](const FGameplayTagContainer& TagsContainer)
		{
			for (const FGameplayTag& tag : TagsContainer)
			{
				GEngine->AddOnScreenDebugMessage(-1, 3.f, FColor::MakeRandomColor(), *tag.ToString());
			}
		});
	}
}

void UOverlayWidgetController::HealthChanged(const FOnAttributeChangeData& Data) const
{
	OnHealthChanged.Broadcast(Data.NewValue);
}

void UOverlayWidgetController::MAXHealthChanged(const FOnAttributeChangeData& Data) const
{
	OnMAXHealthChanged.Broadcast(Data.NewValue);
}

void UOverlayWidgetController::ManaChanged(const FOnAttributeChangeData& Data) const
{
	OnManaChanged.Broadcast(Data.NewValue);
}

void UOverlayWidgetController::MAXManaChanged(const FOnAttributeChangeData& Data) const
{
	OnMAXManaChanged.Broadcast(Data.NewValue);
}

void UOverlayWidgetController::BroadcastInitializeValues()
{
	const UAuraAttributeSet* ASInOverlayCtrl = Cast<UAuraAttributeSet>(ASInWidController);
	OnHealthChanged.Broadcast(ASInOverlayCtrl->GetHealth());
	OnMAXHealthChanged.Broadcast(ASInOverlayCtrl->GetMaxHealth());
	OnManaChanged.Broadcast(ASInOverlayCtrl->GetMana());
	OnMAXManaChanged.Broadcast(ASInOverlayCtrl->GetMaxMana());
}
