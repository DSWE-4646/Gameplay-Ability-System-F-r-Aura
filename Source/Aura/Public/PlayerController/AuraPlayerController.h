// SiberianSledCat

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "Interface/HighlightActorInterface.h"
#include "GameplayTagContainer.h"
#include "PlayerController/Input/AuraInputComponent.h"
#include "AuraPlayerController.generated.h"


class USplineComponent;
class UAuraAbilitySystemComponent;
class UAuraInputConfig;
struct FInputActionValue;
class UInputAction;
class UInputMappingContext;
/**
 * 
 */
UCLASS()
class AURA_API AAuraPlayerController : public APlayerController
{
	GENERATED_BODY()
public:
	AAuraPlayerController();

	UAuraAbilitySystemComponent* GetAuraASC();

protected:
	virtual void BeginPlay() override;
	virtual void SetupInputComponent() override;
	
private:
	UPROPERTY(EditAnywhere, Category = "Input")
	TObjectPtr<UInputAction> AuraMoveAction;
	
	UPROPERTY(EditAnywhere, Category = "Input")
	TObjectPtr<UInputMappingContext> AuraMappingContext;
	
	void AuraMove(const FInputActionValue& AuraInputActionValue);

	virtual void PlayerTick(float DeltaTime) override;

	void CursorTrace();
	TWeakInterfacePtr<IHighlightActorInterface> LastActor;
	TWeakInterfacePtr<IHighlightActorInterface> CurrentActor;

	/*  存储输入配置，其中是IA与对应的Tag */
	UPROPERTY(EditDefaultsOnly, Category = "Input")
	TObjectPtr<UAuraInputConfig> InputConfig;

	/**
	 * @brief 技能输入按下事件回调
	 * 
	 * 当玩家按下技能输入按键时触发。该函数会将输入标签传递给能力系统组件(GAS)，
	 * 用于激活对应的能力(Ability)。通常用于立即触发的技能或开始蓄力技能。
	 * 
	 * @param GameplayTag 与输入动作关联的游戏标签，用于标识具体哪个技能被触发
	 */
	void AbilityInputTagpressed(FGameplayTag GameplayTag);

	/**
	 * @brief 技能输入释放事件回调
	 * 
	 * 当玩家释放技能输入按键时触发。该函数通知能力系统组件输入已释放，
	 * 用于结束持续施法技能或确定蓄力技能的最终效果。例如：蓄力攻击在释放时
	 * 根据蓄力时长决定伤害大小。
	 * 
	 * @param GameplayTag 与输入动作关联的游戏标签，用于标识具体哪个技能被释放
	 */
	void AbilityInputTagReleased(FGameplayTag GameplayTag);

	/**
	 * @brief 技能输入按住事件回调
	 * 
	 * 当玩家持续按住技能输入按键时触发（每帧检测）。该函数用于处理需要持续施法
	 * 或蓄力的技能，例如：持续引导类技能、蓄力攻击等。按住期间会不断通知能力
	 * 系统组件输入状态，实现平滑的持续效果。
	 * 
	 * @param GameplayTag 与输入动作关联的游戏标签，用于标识具体哪个技能正在按住
	 */
	void AbilityInputTagHold(FGameplayTag GameplayTag);

	UPROPERTY()
	TObjectPtr<UAuraAbilitySystemComponent> AuraASC;

	/*  长按移动相关 */
	FVector DestinationLocation = FVector::ZeroVector;
	float PressTime = 0.f;
	float ValveTime = .5f;
	bool bIsAutoMove = false;
	bool bIsTargeting = false;

	/*  自动接受范围 */
	UPROPERTY(EditDefaultsOnly, Category = "Input")
	float AutoAcceptanceRadius = 50.f;

	/*  移动路径 */
	UPROPERTY(EditAnywhere, Category = "Input")
	TObjectPtr<USplineComponent> PCSplineComponent;
};
