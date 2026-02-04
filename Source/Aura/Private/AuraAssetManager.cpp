// SiberianSledCat


#include "AuraAssetManager.h"

#include "AuraGameplayTags.h"

UAuraAssetManager& UAuraAssetManager::Get()
{
	checkf(GEngine, TEXT("Engine is not available!"));
	UAuraAssetManager* AssetManager = Cast<UAuraAssetManager>(GEngine->AssetManager);
	return *AssetManager;
}

void UAuraAssetManager::StartInitialLoading()
{
	Super::StartInitialLoading();

}
