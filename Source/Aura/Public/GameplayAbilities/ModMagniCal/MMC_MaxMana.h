// SiberianSledCat

#pragma once

#include "CoreMinimal.h"
#include "GameplayModMagnitudeCalculation.h"
#include "MMC_MaxMana.generated.h"

/**
 * 
 */
UCLASS()
class AURA_API UMMC_MaxMana : public UGameplayModMagnitudeCalculation
{
	GENERATED_BODY()

public:
	//构造函数捕获Vigor属性并添加到被捕获列表中
	UMMC_MaxMana();

	//计算被捕获列表中属性的值，并返回计算结果给ModifierInfo
	virtual float CalculateBaseMagnitude_Implementation(const FGameplayEffectSpec& Spec) const override;

private:
	//暂存被捕获用于计算的属性
	FGameplayEffectAttributeCaptureDefinition IntelliDef;
};
