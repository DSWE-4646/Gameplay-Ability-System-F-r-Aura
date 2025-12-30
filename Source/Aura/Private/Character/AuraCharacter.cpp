// SiberianSledCat


#include "Character/AuraCharacter.h"

#include "Camera/CameraComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameplayAbilities/AuraAbilitySystemComponent.h"
#include "GameplayAbilities/AuraAttributeSet.h"
#include "PlayerController/AuraPlayerController.h"
#include "PlayerState/AuraPlayerState.h"
#include "UI/HUD/AuraHUD.h"

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

	InitAbilityActorInfoInCharac();
}

void AAuraCharacter::OnRep_PlayerState()
{
	Super::OnRep_PlayerState();

	InitAbilityActorInfoInCharac();
}

void AAuraCharacter::InitAbilityActorInfoInCharac()
{
	AAuraPlayerState* AuraPlayerState = GetPlayerState<AAuraPlayerState>();
	checkf(AuraPlayerState, TEXT("Get AAuraPlayerState failed in PossessBy"));
	AuraPlayerState->GetAbilitySystemComponent()->InitAbilityActorInfo(AuraPlayerState, this);
	AbilitySystemInCharac = AuraPlayerState->GetAbilitySystemComponent();
	AttributeSetInCharac = AuraPlayerState->GetAttributeSet();

	if (UAuraAbilitySystemComponent* AuraASC = Cast<UAuraAbilitySystemComponent>(AbilitySystemInCharac))
	{
		AuraASC->AbilityActorInfoSet();
	}
	
	if (AAuraPlayerController* AuraPlayerController  = Cast<AAuraPlayerController>(GetController()))
	{
		AAuraHUD* AuraHUD = Cast<AAuraHUD>(AuraPlayerController->GetHUD());
		AuraHUD->InitializeOverlayWidget(AbilitySystemInCharac, AuraPlayerController, AuraPlayerState, AttributeSetInCharac);
	}
}
