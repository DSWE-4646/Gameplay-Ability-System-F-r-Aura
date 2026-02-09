// SiberianSledCat


#include "GameplayAbilities/Data/AttributeInfo.h"

FAuraAttributeInfo UAttributeInfo::FindAttributeInfo(const FGameplayTag& AttributeTag, bool bLogNotFound ) const
{
	for (const FAuraAttributeInfo& info : AttributeInformation)
	{
		if (info.AttributeTag.MatchesTagExact(AttributeTag))
		{
			return info;
		}
	}

	
	if (bLogNotFound)
	{
		UE_LOG(LogTemp, Error, TEXT("无法找到AttributeTag: %s 在 AttributeInfo: %s 中"),
			*AttributeTag.ToString(),
			*GetNameSafe(this)); //GetNameSafe() 防止this为空时崩溃,相比于GetName() 会先判断指针是否存在
	}
	return FAuraAttributeInfo();
}
