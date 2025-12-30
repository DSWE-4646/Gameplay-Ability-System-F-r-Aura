// SiberianSledCat

#pragma once

#include "CoreMinimal.h"
#include "Character/AuraBaseCharacter.h"
#include "AuraCharacter.generated.h"

class USpringArmComponent;
class UCameraComponent;
/**
 * 
 */
UCLASS()
class AURA_API AAuraCharacter : public AAuraBaseCharacter
{
	GENERATED_BODY()
public:
	AAuraCharacter();

	virtual void PossessedBy(AController* NewController) override; //F12 make sure it's a public func
	virtual void OnRep_PlayerState() override; //Also Public in Pawn Class
private:
	UPROPERTY(EditAnywhere)
	USpringArmComponent* AuraSpringArm;

	UPROPERTY(EditAnywhere)
	UCameraComponent* AuraDefaultCamera;

	virtual void InitAbilityActorInfoInCharac() override;
};
