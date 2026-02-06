// SiberianSledCat


#include "UI/Controller/OverlayWidgetController.h"

#include "GameplayAbilities/AuraAttributeSet.h"



void UOverlayWidgetController::BindCallbacksToDependencies()
{
	if (!ASCInWidController || !ASInWidController) return;

	UAuraAttributeSet* AuraAS = Cast<UAuraAttributeSet>(ASInWidController);
	if (!AuraAS) return;
	
	ASCInWidController -> GetGameplayAttributeValueChangeDelegate(AuraAS->GetHealthAttribute()).AddLambda(
	[this](const FOnAttributeChangeData& Data)
	{
		OnHealthChanged.Broadcast(Data.NewValue);
	});
	
	ASCInWidController -> GetGameplayAttributeValueChangeDelegate(AuraAS->GetMaxHealthAttribute()).AddLambda(
	[this](const FOnAttributeChangeData& Data)
		{
			OnMAXHealthChanged.Broadcast(Data.NewValue);
		});
	
	ASCInWidController -> GetGameplayAttributeValueChangeDelegate(AuraAS->GetManaAttribute()).AddLambda(
	[this](const FOnAttributeChangeData& Data)
		{
			OnManaChanged.Broadcast(Data.NewValue);
		});
	
	ASCInWidController -> GetGameplayAttributeValueChangeDelegate(AuraAS->GetMaxManaAttribute()).AddLambda(
	[this](const FOnAttributeChangeData& Data)
		{
			OnMAXManaChanged.Broadcast(Data.NewValue);
		});

	/* 在游戏效果应用时显示相应的 UI 消息 */
	if (UAuraAbilitySystemComponent* AuraASC = Cast<UAuraAbilitySystemComponent>(ASCInWidController))
	{
		AuraASC->EffectAssetTags.AddLambda([this](const FGameplayTagContainer& TagsContainer)
		{
			const FGameplayTag MessageRootTag = FGameplayTag::RequestGameplayTag(FName("Message"));
			for (const FGameplayTag& tag : TagsContainer)
			{
				if (tag.MatchesTag(MessageRootTag))
				{
					if (!MessageWidgetDataTable) 
					UE_LOG(LogTemp, Error, TEXT("MessageWidgetDataTable is not set in OverlayWidgetController"));
						
					FUIWidgetRow* Row = GetDataTableRowbyTag<FUIWidgetRow>(MessageWidgetDataTable, tag);
				
				if (Row)
					MessageWidgetRowSignature.Broadcast(*Row);
				}
			}
		});
	}
}

void UOverlayWidgetController::BroadcastInitializeValues()
{
	const UAuraAttributeSet* ASInOverlayCtrl = Cast<UAuraAttributeSet>(ASInWidController);
	OnHealthChanged.Broadcast(ASInOverlayCtrl->GetHealth());
	OnMAXHealthChanged.Broadcast(ASInOverlayCtrl->GetMaxHealth());
	OnManaChanged.Broadcast(ASInOverlayCtrl->GetMana());
	OnMAXManaChanged.Broadcast(ASInOverlayCtrl->GetMaxMana());
}
