// SiberianSledCat


#include "PlayerController/AuraPlayerController.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"
#include "InputAction.h"

AAuraPlayerController::AAuraPlayerController()
{
	bReplicates = true;
}

void AAuraPlayerController::BeginPlay()
{
	Super::BeginPlay();

	checkf(AuraMappingContext, TEXT("AuraMappingContext Init Failed"));

	UEnhancedInputLocalPlayerSubsystem* AuraEInputSusyem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer());
	checkf(AuraEInputSusyem, TEXT("Get EnhancedInputLocalPlayerSubsystem Failed"));

	AuraEInputSusyem->AddMappingContext(AuraMappingContext, 0); //由于增强输入允许多个上下文因此设置优先度
	bShowMouseCursor = true;
	DefaultMouseCursor = EMouseCursor::Default;

	FInputModeGameAndUI AuraInputMode;
	AuraInputMode.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);
	AuraInputMode.SetHideCursorDuringCapture(false);
	SetInputMode(AuraInputMode);
}

void AAuraPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	UEnhancedInputComponent* AuraInputComponent = CastChecked<UEnhancedInputComponent>(InputComponent);
	AuraInputComponent->BindAction(AuraMoveAction, ETriggerEvent::Triggered, this, &AAuraPlayerController::AuraMove);
}

void AAuraPlayerController::AuraMove(const FInputActionValue& AuraInputActionValue)
{
	const FVector2D InputVecorAxisXY = AuraInputActionValue.Get<FVector2D>();
	const FRotator AuraRotation = {0.f, GetControlRotation().Yaw, 0.f}; //FRotator(0.f, GetControlRotation().Yaw, 0.f)

	const FVector ForwardVector = FRotationMatrix(AuraRotation).GetUnitAxis(EAxis::X);
	const FVector RightVector = FRotationMatrix(AuraRotation).GetUnitAxis(EAxis::Y);

	if (APawn* AuraPawn = GetPawn())
	{
		AuraPawn->AddMovementInput(ForwardVector, InputVecorAxisXY.Y);
		AuraPawn->AddMovementInput(RightVector, InputVecorAxisXY.X);
	}
}

void AAuraPlayerController::PlayerTick(float DeltaTime)
{
	Super::PlayerTick(DeltaTime);
	CursorTrace();
}

void AAuraPlayerController::CursorTrace()
{
	FHitResult CursorHit;
	GetHitResultUnderCursor(ECC_Visibility, false, CursorHit);
	if (!CursorHit.bBlockingHit) return;

	LastActor = CurrentActor;
	CurrentActor = Cast<IHighlightActorInterface>(CursorHit.GetActor());
	
	if (LastActor == nullptr)
	{
		if (CurrentActor == nullptr)
		{
			//UE_LOG(LogTemp, Log, TEXT("No Valid Actor Pointed by Cursor"));
		}
		else
		{
			CurrentActor->HighlightActor();
		}
	}
	else
	{
		if (CurrentActor == nullptr)
		{
			LastActor->UnHighlightActor();
		}
		else
		{
			if (LastActor != CurrentActor)
			{
				LastActor->UnHighlightActor();
				CurrentActor->HighlightActor();
			}
			else
			{
				
			}
		}
	}
		
}
