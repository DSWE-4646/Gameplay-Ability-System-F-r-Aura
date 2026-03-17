// SiberianSledCat

#pragma once

#include "CoreMinimal.h"
#include "EnhancedInputComponent.h"
#include "GameplayAbilities/GameplayAbility/AuraInputConfig.h"
#include "AuraInputComponent.generated.h"


UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class AURA_API UAuraInputComponent : public UEnhancedInputComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UAuraInputComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType,
	                           FActorComponentTickFunction* ThisTickFunction) override;

	template<class UserClass, typename PressFuncType, typename ReleaseFuncType, typename HoldFuncType>
	void BindAbilityActions(const UAuraInputConfig* InputConfig,
		UserClass* Object,
		PressFuncType PressFunc,
		ReleaseFuncType ReleaseFunc,
		HoldFuncType HoldFunc);
};

template <class UserClass, typename PressFuncType, typename ReleaseFuncType, typename HoldFuncType>
void UAuraInputComponent::BindAbilityActions(const UAuraInputConfig* InputConfig,
	UserClass* Object,
	PressFuncType PressFunc,
	ReleaseFuncType ReleaseFunc,
	HoldFuncType HoldFunc)
{
	if (!InputConfig || !Object)
		return;
	for (const auto& Action : InputConfig->InputActions)
	{
		  if (Action.InputAction && Action.ActionTag.IsValid())
		  {
			  // Pressed（Started）
		  	if (PressFunc)
		  	{
		  		//Action.ActionTag是回调函数的参数
		  		BindAction(Action.InputAction, ETriggerEvent::Started, Object, PressFunc, Action.ActionTag);
		  	}
		  	// Released（Completed）
		  	if (ReleaseFunc)
		  	{
		  		BindAction(Action.InputAction, ETriggerEvent::Completed, Object, ReleaseFunc, Action.ActionTag);
		  	}
		  	// Held（Triggered）
		  	if (HoldFunc)
		  	{
		  		BindAction(Action.InputAction, ETriggerEvent::Triggered, Object, HoldFunc, Action.ActionTag);
		  	}
		  }

	}
}
