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
private:
	UPROPERTY(EditAnywhere)
	USpringArmComponent* AuraSpringArm;

	UPROPERTY(EditAnywhere)
	UCameraComponent* AuraDefaultCamera;
};
