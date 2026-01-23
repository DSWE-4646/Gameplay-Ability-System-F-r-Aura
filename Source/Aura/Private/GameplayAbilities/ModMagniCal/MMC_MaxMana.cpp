// SiberianSledCat


#include "GameplayAbilities/ModMagniCal/MMC_MaxMana.h"

#include "GameplayAbilities/AuraAttributeSet.h"
#include "Interface/CombatInterface.h"

UMMC_MaxMana::UMMC_MaxMana()
{
	// 定义Intelli的捕获属性
	IntelliDef.AttributeToCapture  = UAuraAttributeSet::GetIntelligenceAttribute();
	IntelliDef.AttributeSource = EGameplayEffectAttributeCaptureSource::Target;
	IntelliDef.bSnapshot = true;

	//添加到捕获列表
	RelevantAttributesToCapture.Add(IntelliDef);
}

float UMMC_MaxMana::CalculateBaseMagnitude_Implementation(const FGameplayEffectSpec& Spec) const
{
	//获取目标与源的Tag，可选项
	const FGameplayTagContainer* SourceContainer = Spec.CapturedSourceTags.GetAggregatedTags();
	const FGameplayTagContainer* TargetContainer = Spec.CapturedTargetTags.GetAggregatedTags();

	// 创建参数对象，其包括目标与源的Tag、过滤器以及一个bool控制是否开启预测
	FAggregatorEvaluateParameters EvaluationParameters;
	EvaluationParameters.SourceTags = SourceContainer;
	EvaluationParameters.TargetTags = TargetContainer;

	// 获取Intelli的值
	float Intelli = 0.0f;
	GetCapturedAttributeMagnitude(IntelliDef, Spec, EvaluationParameters, Intelli);
	Intelli = FMath::Max(Intelli, 0.0f);

	//获得玩家的Level
	const UObject* Source = Spec.GetContext().GetSourceObject();
	const ICombatInterface* CombatInterface = Cast<ICombatInterface>(Source);
	checkf(CombatInterface, TEXT("Failed to cast Source to ICombatInterface in MMC_MaxHealth"));
	int32 PlayerLevel = CombatInterface->GetLevelAttribute();
	
	// 自定义计算逻辑：MaxMana = 50 + 2.5*Intelligence + 15*PlayerLevel
    const float BaseValue = 50.f;
    const float IntMultiplier = 2.5f;
    const float LevelMultiplier = 15.f;
    return BaseValue + (IntMultiplier * Intelli) + (LevelMultiplier * PlayerLevel);

}
