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
			BroadcastAttributeInfo(Pair.Key, Pair.Value);
		}
	}
}

void UAttributeMenuController::BindCallbacksToDependencies()
{
	UAuraAttributeSet* AS = CastChecked<UAuraAttributeSet>(ASInWidController);

	for (const auto& Pair : AS->TagsToAttributes)
	{
		/* Lambda必须带上FOnAttributeChangeData& Data，
		 * 这是因为GetGameplayAttributeValueChangeDelegate(Pair.Value())这个委托要求一个参数，
		 * 类型为FOnAttributeChangeData&，
		 * Lambda 作为委托的回调，必须严格匹配委托的参数列表和返回值*/
		/*  AddLambda是注册委托，Lambda调用时可能退出循环，因此不能使用&，必须值传递，捕获Pair&会导致循环结束后变成野引用 */
		ASCInWidController->GetGameplayAttributeValueChangeDelegate(Pair.Value()).AddLambda(
			[this, Pair](const FOnAttributeChangeData& Data)
			{
				BroadcastAttributeInfo(Pair.Key, Pair.Value);
			});
	}
}

void UAttributeMenuController::BroadcastAttributeInfo(const FGameplayTag& GameplayTag,
	FAttributeFuncPtr GetAttributeFunction)
{
	UAuraAttributeSet* AS = CastChecked<UAuraAttributeSet>(ASInWidController);
	
	if (!AS || !AttributeInfo)
	{
		UE_LOG(LogTemp, Error, TEXT("AS or AttributeInfo is not set in AttributeMenuController"));
		return;
	}
	
	FAuraAttributeInfo RowAttributeInfo = AttributeInfo->FindAttributeInfo(GameplayTag);
	//Pair.Value是函数指针，必须执行才能获取属性值
	RowAttributeInfo.AttributeValue = GetAttributeFunction().GetNumericValue(AS);
	OnMenuAttributeChanged.Broadcast(RowAttributeInfo);
}
