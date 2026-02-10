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
		/* 遍历AS中的TMap，根据Key获取Tag相应的Info，根据Value获取每个属性后取值，并广播给UI */
		for (const auto& Pair : AS->TagsToAttributes)
		{
			FGameplayTag GameplayTag = Pair.Key;
			FAuraAttributeInfo RowAttributeInfo = AttributeInfo->FindAttributeInfo(GameplayTag);
			//Pair.Value是函数指针，必须执行才能获取属性值
			RowAttributeInfo.AttributeValue = Pair.Value().GetNumericValue(AS);
			OnMenuAttributeChanged.Broadcast(RowAttributeInfo);
		}
	}
}

void UAttributeMenuController::BindCallbacksToDependencies()
{
	Super::BindCallbacksToDependencies();
}
