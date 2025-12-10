// SiberianSledCat


#include "Character/AuraCharacter.h"

#include "Camera/CameraComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameplayAbilities/AuraAbilitySystemComponent.h"
#include "GameplayAbilities/AuraAttributeSet.h"
#include "PlayerState/AuraPlayerState.h"

AAuraCharacter::AAuraCharacter()
{
	AuraSpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("AuraSpringArm"));
	AuraSpringArm ->SetupAttachment(GetRootComponent());
	AuraDefaultCamera =  CreateDefaultSubobject<UCameraComponent>(TEXT("AuraDefaultCamera"));
	AuraDefaultCamera->SetupAttachment(AuraSpringArm);

	AuraSpringArm->bUsePawnControlRotation = false;
	AuraDefaultCamera->bUsePawnControlRotation = false;

	AuraSpringArm->bInheritPitch = false;
	AuraSpringArm->bInheritRoll = false;
	AuraSpringArm->bInheritYaw = false;
	AuraSpringArm->TargetArmLength = 750.f;
	
	bUseControllerRotationPitch = false;
	bUseControllerRotationRoll = false;
	bUseControllerRotationYaw = false;
	
	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->RotationRate = FRotator(0.f, 400.f, 0.f);
	GetCharacterMovement()->bConstrainToPlane = true;
	GetCharacterMovement()->bSnapToPlaneAtStart = true;
	
}

void AAuraCharacter::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);

	InitAbilityActorInfoInAuraCharac();
}

void AAuraCharacter::OnRep_PlayerState()
{
	Super::OnRep_PlayerState();

	InitAbilityActorInfoInAuraCharac();
}

void AAuraCharacter::InitAbilityActorInfoInAuraCharac()
{
	AAuraPlayerState* AuraPlayerState = GetPlayerState<AAuraPlayerState>();
	checkf(AuraPlayerState, TEXT("Get AAuraPlayerState failed in PossessBy"));
	AuraPlayerState->GetAbilitySystemComponent()->InitAbilityActorInfo(AuraPlayerState, this);
	AbilitySystemInCharac = AuraPlayerState->GetAbilitySystemComponent();
	AttributeSetInCharac = AuraPlayerState->GetAttributeSet();
}
