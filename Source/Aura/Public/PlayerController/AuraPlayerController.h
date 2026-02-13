// SiberianSledCat

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "Interface/HighlightActorInterface.h"
#include "GameplayTagContainer.h"
#include "PlayerController/Input/AuraInputComponent.h"
#include "AuraPlayerController.generated.h"


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

	/*  为每个输入创建3种不同的输入回调并绑定Tag */
	void AbilityInputTagpressed(FGameplayTag GameplayTag);
	void AbilityInputTagReleased(FGameplayTag GameplayTag);
	void AbilityInputTagHold(FGameplayTag GameplayTag);
};
