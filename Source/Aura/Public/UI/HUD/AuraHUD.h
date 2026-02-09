// SiberianSledCat

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "AuraHUD.generated.h"

class UAttributeMenuController_Deprecated;
class UAbilitySystemComponent;
class UAttributeSet;
struct FAuraWidgetControllerParams;
class UOverlayWidgetController;
class UAuraUserWidget;
/**
 * 
 */
UCLASS()
class AURA_API AAuraHUD : public AHUD
{
	GENERATED_BODY()

public:
	UOverlayWidgetController* GetOverlayWidgetController(const FAuraWidgetControllerParams& FAWCtrlParams);

	UFUNCTION(BlueprintCallable, Category = "Widget Controller")
	UAttributeMenuController_Deprecated* GetAttributeMenuController();

	void InitializeOverlayWidget(UAbilitySystemComponent* ASCParam, APlayerController* PCParam, APlayerState* PSParam, UAttributeSet* ASParam);
protected:
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UAuraUserWidget> OverlayWidgetClass;

	UPROPERTY()
	TObjectPtr<UAuraUserWidget> DisplayWidget;

	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<UOverlayWidgetController> OverlayWidCtlInHUD  = nullptr;

	UPROPERTY(EditAnywhere)
	TSubclassOf<UOverlayWidgetController> OverlayWidCtlInHUDSubclass;

private:
	UAttributeMenuController_Deprecated* AttributeMenuController = nullptr;
	
};
