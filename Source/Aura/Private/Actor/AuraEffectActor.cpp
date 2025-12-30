// SiberianSledCat


#include "Actor/AuraEffectActor.h"

#include "AbilitySystemBlueprintLibrary.h"
#include "AbilitySystemComponent.h"

// Sets default values
AAuraEffectActor::AAuraEffectActor()
{
	//SceneRoot = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));
	//SetRootComponent(SceneRoot);
}

void AAuraEffectActor::ApplyEffectToTarget(AActor* TargetActor, TSubclassOf<UGameplayEffect> GameplayEffectClass)
{
	UAbilitySystemComponent* TargetASC =  UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(TargetActor);
	//UAbilitySystemComponent* TargetASC = Cast<UAbilitySystemComponent>(Target); //通过接口方法，有警告
	if (!TargetASC)   return;

	checkf(GameplayEffectClass, TEXT("GameplayEffectClass doesn't Set!"));
	FGameplayEffectContextHandle EffectContextHandle = TargetASC->MakeEffectContext();
	EffectContextHandle.AddSourceObject(this);
	FGameplayEffectSpecHandle EffectSpecHandle =  TargetASC->MakeOutgoingSpec(GameplayEffectClass, Actorlevel, EffectContextHandle);

	/** New in 移除无限GE与无限GE堆叠 */
	if (FGameplayEffectSpec* spec = EffectSpecHandle.Data.Get())
	{
		/* Get GE from SpecHandle */
		const UGameplayEffect* GameplayEffect = spec->Def.Get();
		if (GameplayEffect)
		{
			/* Judge Is infinite from GE */
			const bool bIsInfinite = (GameplayEffect->DurationPolicy == EGameplayEffectDurationType::Infinite);

			/* Apply the effect */
			const FActiveGameplayEffectHandle ActiveGameplayEffectHandle = TargetASC->ApplyGameplayEffectSpecToSelf(*spec);

			/* Only store Infinite effects for later removal */
			if (bIsInfinite && ActiveGameplayEffectHandle.IsValid())
			{
				ActiveEffectHandles.Add(ActiveGameplayEffectHandle, TargetASC);
			}
		}
	}
}

void AAuraEffectActor::OnOverlap(AActor* TargetActor)
{
	if (!TargetActor) return;
	if (InstantEffectApplicationPolicy == EEffectApplicationPolicy::ApplyOnOverlap)
	{
		ApplyEffectToTarget(TargetActor, InstanceGameplayEffectClass);
	}
	if (DurationEffectApplicationPolicy == EEffectApplicationPolicy::ApplyOnOverlap)
	{
		ApplyEffectToTarget(TargetActor, DurationGameplayEffectClass);
	}
	if (InfiniteEffectApplicationPolicy == EEffectApplicationPolicy::ApplyOnOverlap)
	{
		ApplyEffectToTarget(TargetActor, InfiniteGameplayEffectClass);
	}
}

void AAuraEffectActor::OnEndOverlap(AActor* TargetActor)
{
	if (InstantEffectApplicationPolicy == EEffectApplicationPolicy::ApplyOnEndOverlap)
	{
		ApplyEffectToTarget(TargetActor, InstanceGameplayEffectClass);
	}
	if (DurationEffectApplicationPolicy == EEffectApplicationPolicy::ApplyOnEndOverlap)
	{
		ApplyEffectToTarget(TargetActor, DurationGameplayEffectClass);
	}

	/* Remove Infinite GE */
	UAbilitySystemComponent* TargetASC =  UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(TargetActor);
	if (!IsValid(TargetASC)) return;
	TArray<FActiveGameplayEffectHandle> HandlesToRemove;
	for (const auto& HandlePair : ActiveEffectHandles)
	{
		const FActiveGameplayEffectHandle& EffectHandle = HandlePair.Key;
		UAbilitySystemComponent* StoreASC = HandlePair.Value;
		if (StoreASC == TargetASC && EffectHandle.IsValid())
		{
			TargetASC->RemoveActiveGameplayEffect(EffectHandle, 1);
			HandlesToRemove.Add(EffectHandle);
		}
	}
	/* Remove from TArray */
	for (const FActiveGameplayEffectHandle& EffectHandle : HandlesToRemove)
	{
		ActiveEffectHandles.Remove(EffectHandle);
	}
	
}

