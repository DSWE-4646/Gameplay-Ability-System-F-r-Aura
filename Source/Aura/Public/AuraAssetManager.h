// SiberianSledCat

#pragma once

#include "CoreMinimal.h"
#include "AuraGameplayTags.h"
#include "Engine/AssetManager.h"
#include "AuraAssetManager.generated.h"

/**
 * 
 */
UCLASS()
class AURA_API UAuraAssetManager : public UAssetManager
{
	GENERATED_BODY()

public:
	/* 获取UAssetManager的单例转换成UAuraAssetManager并返回 */
	static UAuraAssetManager& Get();
	

protected:
	/* 调用UAuraGameplayTags的初始化函数，注册Native GameplayTag */
	virtual void StartInitialLoading() override;

private:
};
