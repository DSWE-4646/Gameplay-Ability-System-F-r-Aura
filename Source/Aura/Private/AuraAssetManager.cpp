// SiberianSledCat


#include "AuraAssetManager.h"

#include "AuraGameplayTags.h"

UAuraAssetManager& UAuraAssetManager::Get()
{
	checkf(GEngine, TEXT("Engine is not available!"));
	/*脚本中的操作导致加载的AssetManager实际是一个UAuraAssetManager，因此Cast必定成功*/
	UAuraAssetManager* AssetManager = Cast<UAuraAssetManager>(GEngine->AssetManager);
	return *AssetManager;
}

void UAuraAssetManager::StartInitialLoading()
{
	Super::StartInitialLoading();

	FAuraGameplayTags::InitializeGameplayTags();
}

