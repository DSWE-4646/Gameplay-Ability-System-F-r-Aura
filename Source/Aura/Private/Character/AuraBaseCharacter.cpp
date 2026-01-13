// SiberianSledCat


#include "Character/AuraBaseCharacter.h"

#include "AbilitySystemComponent.h"

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
	//checkf(IsValid(DefaultPrimaryAttributeGE), TEXT("DefaultPrimaryAttributeGE is not valid"));
	if (!IsValid(DefaultPrimaryAttributeGE)) 
	{
		UE_LOG(LogTemp, Warning, TEXT("DefaultPrimaryAttributeGE is not valid"));
		return;
	}

	UAbilitySystemComponent* ASC = GetAbilitySystemComponent();
	if (!IsValid(ASC)) 
	{
		UE_LOG(LogTemp, Warning, TEXT("AbilitySystemComponent is not valid"));
		return;
	}
	
		FGameplayEffectContextHandle Context = ASC->MakeEffectContext();
		FGameplayEffectSpecHandle Spec =ASC->MakeOutgoingSpec(DefaultPrimaryAttributeGE,
		1.f,
		Context);
	
	if (!Spec.IsValid())
	{
		UE_LOG(LogTemp, Warning, TEXT("Failed to create GameplayEffectSpec"));
		return;
	}
	ASC->ApplyGameplayEffectSpecToTarget(*Spec.Data.Get(), ASC);
	
}




