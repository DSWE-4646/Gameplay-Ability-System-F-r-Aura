// SiberianSledCat


#include "PlayerController/AuraPlayerController.h"

#include "AbilitySystemBlueprintLibrary.h"
#include "AuraGameplayTags.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"
#include "GameplayAbilities/AuraAbilitySystemComponent.h"
#include "InputAction.h"
#include "Components/SplineComponent.h"

AAuraPlayerController::AAuraPlayerController()
{
	bReplicates = true;

	PCSplineComponent = CreateDefaultSubobject<USplineComponent>(TEXT("PCSplineComponent"));

	
}

UAuraAbilitySystemComponent* AAuraPlayerController::GetAuraASC()
{
	if (!AuraASC)
		AuraASC = Cast<UAuraAbilitySystemComponent>(
            UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(GetPawn())
        );

	return AuraASC;
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
	/* 在没有在项目设置或者配置文件中 使用自定义输入组件的情况下 应当这样设置 
	// 先创建自定义的 InputComponent
	InputComponent = NewObject<UAuraInputComponent>(this, TEXT("InputComponent"));
	InputComponent->RegisterComponent();
	*/
	
	Super::SetupInputComponent();

	/*  使用自定义输入组件，调用其中的模板函数传入当前的3个函数 */
	UAuraInputComponent* AuraInputComponent = CastChecked<UAuraInputComponent>(InputComponent);
	AuraInputComponent->BindAction(AuraMoveAction, ETriggerEvent::Triggered, this, &AAuraPlayerController::AuraMove);

	AuraInputComponent->BindAbilityActions(InputConfig,
		this,
		&ThisClass::AbilityInputTagpressed,
		&ThisClass::AbilityInputTagReleased,
		&ThisClass::AbilityInputTagHold
		);
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

void AAuraPlayerController::AbilityInputTagpressed( FGameplayTag GameplayTag)
{
	if (GameplayTag.MatchesTagExact(FAuraGameplayTags::Get().InputTag_LMB))
	{
		bIsTargeting = (CurrentActor != nullptr);
		bIsAutoMove = false;
		PressTime = 0.f; //重置按键时间
	}
}

void AAuraPlayerController::AbilityInputTagReleased(FGameplayTag GameplayTag)
{
	if (!GetAuraASC()) return;
	AuraASC->AbilityInputTagReleased(GameplayTag);

	
}

void AAuraPlayerController::AbilityInputTagHold(FGameplayTag GameplayTag)
{
	// 不是左键 → 激活技能并返回
	if (!GameplayTag.MatchesTagExact(FAuraGameplayTags::Get().InputTag_LMB))
	{
		if (!GetAuraASC()) return;
		AuraASC->AbilityInputTagHeld(GameplayTag);
		return; //非LMB按键释放技能后跳出
	}

	// 是左键且瞄准敌人 → 激活技能并返回
	if (bIsTargeting)
	{
		if (!GetAuraASC()) return;
		AuraASC->AbilityInputTagHeld(GameplayTag);
		return; //正在锁定目标，跳出
	}

	// 以下是 Click to Move 逻辑（只有：左键 + 未瞄准敌人才执行）
	// 短按阈值检查
	PressTime += GetWorld()->GetDeltaSeconds();
	if (PressTime < ValveTime)
		return;
	
	FHitResult CursorHit;
	if (GetHitResultUnderCursor(ECC_Visibility, false, CursorHit))
	DestinationLocation = CursorHit.Location;

	
	if (APawn* ControllerPawn = GetPawn())
	{
		const FVector DestinationDirection = (DestinationLocation - ControllerPawn->GetActorLocation()).GetSafeNormal();
		ControllerPawn->AddMovementInput(DestinationDirection, 1.f);
	}
	
}
