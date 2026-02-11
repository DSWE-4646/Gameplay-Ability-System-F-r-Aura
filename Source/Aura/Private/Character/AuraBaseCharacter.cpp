// SiberianSledCat


#include "Character/AuraBaseCharacter.h"

#include "AbilitySystemComponent.h"
#include "GameplayAbilities/AuraAbilitySystemComponent.h"
#include "GameplayAbilities/GameplayAbility/AuraGameplayAbility.h"

// Sets default values
AAuraBaseCharacter::AAuraBaseCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Weapon = CreateDefaultSubobject<USkeletalMeshComponent>("Weapon");
	Weapon->SetupAttachment(GetMesh(), "HandWeaponSocket");
	Weapon->SetCollisionEnabled(ECollisionEnabled::NoCollision);
}

// Called when the game starts or when spawned
void AAuraBaseCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

UAbilitySystemComponent* AAuraBaseCharacter::GetAbilitySystemComponent() const
{
	return AbilitySystemInCharac;
}

UAttributeSet* AAuraBaseCharacter::GetAttributeSet() const
{
	return AttributeSetInCharac;
}

void AAuraBaseCharacter::InitAbilityActorInfoInCharac()
{
}

void AAuraBaseCharacter::InitDefaultAttributes() const
{
	ApplyGEToSelfForInit(DefaultPrimaryAttributeGE, 1.f);
	ApplyGEToSelfForInit(SecondaryAttributeGE, 1.f);
	// 延迟1帧执行Vital GE，等待Secondary GE完成派生
	ApplyGEToSelfForInit(DefaultVitalAttributeGE, 1.f);
	//ApplyGEToSelfForInit(DefaultVitalAttributeGE, 1.f);
}

void AAuraBaseCharacter::ApplyGEToSelfForInit(TSubclassOf<UGameplayEffect> GEClass, float Level) const
{
	//checkf(IsValid(DefaultPrimaryAttributeGE), TEXT("DefaultPrimaryAttributeGE is not valid"));
	if (!IsValid(GEClass)) 
	{
		UE_LOG(LogTemp, Warning, TEXT("GEClass is not valid"));
		return;
	}

	UAbilitySystemComponent* ASC = GetAbilitySystemComponent();
	if (!IsValid(ASC)) 
	{
		UE_LOG(LogTemp, Warning, TEXT("AbilitySystemComponent is not valid"));
		return;
	}
	
	FGameplayEffectContextHandle Context = ASC->MakeEffectContext();
	Context.AddSourceObject(this); // 添加自身作为Context的SourceObject,否则MMC中将无法获取到Self的level
	FGameplayEffectSpecHandle Spec =ASC->MakeOutgoingSpec(GEClass,
	Level,
	Context);
	
	if (!Spec.IsValid())
	{
		UE_LOG(LogTemp, Warning, TEXT("Failed to create GameplayEffectSpec"));
		return;
	}
	UE_LOG(LogTemp, Warning, TEXT("The %s GE will be applied to self"), *GEClass->GetName());
	ASC->ApplyGameplayEffectSpecToTarget(*Spec.Data.Get(), ASC);
}

void AAuraBaseCharacter::AddCharacterAbilities() const
{
	if (!HasAuthority())
		return;

	UAuraAbilitySystemComponent* AuraASC = CastChecked<UAuraAbilitySystemComponent>(AbilitySystemInCharac);
	
	AuraASC->AddCharacterAbilities(StartupAbilities);
}




