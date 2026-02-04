// SiberianSledCat

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "AuraGameplayTags.generated.h"

USTRUCT()
struct FAuraGameplayTags
{
	GENERATED_BODY()
public:
	FAuraGameplayTags();
	static const FAuraGameplayTags& Get();
	static void InitializeGameplayTags();
	static FAuraGameplayTags Attribute_Secondary_Armor;

protected:

private:
	static FAuraGameplayTags GameplayTags;
	
};
