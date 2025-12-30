// SiberianSledCat


#include "Character/AuraBaseCharacter.h"

#include "AttributeSet.h"

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

void AAuraBaseCharacter::InitAbilityActorInfoInAuraCharac()
{
}




