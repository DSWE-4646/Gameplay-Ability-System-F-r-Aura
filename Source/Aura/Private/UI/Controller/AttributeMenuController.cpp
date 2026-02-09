// SiberianSledCat


#include "UI/Controller/AttributeMenuController.h"

#include "AuraGameplayTags.h"
#include "GameplayAbilities/AuraAttributeSet.h"
#include "GameplayAbilities/Data/AttributeInfo.h"


void UAttributeMenuController::BroadcastInitializeValues()
{
	// ASInWidController 被在AuraHUD的Get初始化时赋值
	UAuraAttributeSet* AS = CastChecked<UAuraAttributeSet>(ASInWidController);
	if (AttributeInfo)
	{
		const FGameplayTag StrengthTag = FAuraGameplayTags::Get().Attributes_Primary_Strength;
		FAuraAttributeInfo Info = AttributeInfo->FindAttributeInfo(StrengthTag);
		Info.AttributeValue = AS->GetStrength();
	}
}

void UAttributeMenuController::BindCallbacksToDependencies()
{
	Super::BindCallbacksToDependencies();
}
