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
	InitAbilityActorInfoInCharac();
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

/* 为了可读性、一致性、可维护性、可拓展性，又把逻辑从Beginplay
 * 移到这里，在InitAbilityActorInfoInCharac中调用 */
void AAuraEnemy::InitAbilityActorInfoInCharac()
{
	Super::InitAbilityActorInfoInCharac();

	checkf(AbilitySystemInCharac,TEXT("Enemy AbilitySystemInCharac Init Failed!"));
	AbilitySystemInCharac->InitAbilityActorInfo(this, this);
	
	if (UAuraAbilitySystemComponent* AuraAbilitySystemComponent = Cast<UAuraAbilitySystemComponent>(AbilitySystemInCharac))
	{
		AuraAbilitySystemComponent->AbilityActorInfoSet();
	}
}

