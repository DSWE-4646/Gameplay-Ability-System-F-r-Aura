// SiberianSledCat

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "Interface/HighlightActorInterface.h"
#include "AuraPlayerController.generated.h"


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
};
