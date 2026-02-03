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

protected:

private:
	static FAuraGameplayTags GameplayTags;
	static void InitializeGameplayTags();
};
