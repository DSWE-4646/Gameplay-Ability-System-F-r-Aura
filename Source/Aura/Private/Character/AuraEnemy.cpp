// SiberianSledCat


#include "Character/AuraEnemy.h"

#include "Aura/Aura.h"
#include "GameplayAbilities/AuraAbilitySystemComponent.h"
#include "GameplayAbilities/AuraAttributeSet.h"


// Sets default values
AAuraEnemy::AAuraEnemy()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	GetMesh()->SetCollisionResponseToChannel(ECC_Visibility, ECR_Block);

	AbilitySystemInCharac = CreateDefaultSubobject<UAuraAbilitySystemComponent>("ASCInEnemy");
	AbilitySystemInCharac->SetIsReplicated(true);
	AbilitySystemInCharac->SetReplicationMode(EGameplayEffectReplicationMode::Minimal);

	AttributeSetInCharac = CreateDefaultSubobject<UAuraAttributeSet>("AttributeSetInEnemy");
}

// Called when the game starts or when spawned
void AAuraEnemy::BeginPlay()
{
	Super::BeginPlay();
	checkf(AbilitySystemInCharac,TEXT("Enemy AbilitySystemInCharac Init Failed!"));
	AbilitySystemInCharac->InitAbilityActorInfo(this, this);
}

// Called every frame
void AAuraEnemy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

// Called to bind functionality to input
void AAuraEnemy::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

void AAuraEnemy::HighlightActor()
{
	//bIsHighlighted = true;
	GetMesh()->SetRenderCustomDepth(true);
	GetMesh()->SetCustomDepthStencilValue(CUSTOM_DEPTHVALUE_RED);
	Weapon->SetRenderCustomDepth(true);
	Weapon->SetCustomDepthStencilValue(CUSTOM_DEPTHVALUE_RED);
}

void AAuraEnemy::UnHighlightActor()
{
	//bIsHighlighted = false;
	GetMesh()->SetRenderCustomDepth(false);
	Weapon->SetRenderCustomDepth(false);
}

