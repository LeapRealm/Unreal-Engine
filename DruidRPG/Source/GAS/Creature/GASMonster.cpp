#include "Creature/GASMonster.h"

#include "GASAbilitySystemComponent.h"
#include "GASAttributeSet.h"
#include "GASUserWidget.h"
#include "Components/WidgetComponent.h"

AGASMonster::AGASMonster()
{
	AbilitySystemComponent = CreateDefaultSubobject<UGASAbilitySystemComponent>(TEXT("AbilitySystemComponent"));
	AbilitySystemComponent->SetIsReplicated(true);
	AbilitySystemComponent->SetReplicationMode(EGameplayEffectReplicationMode::Minimal);

	AttributeSet = CreateDefaultSubobject<UGASAttributeSet>(TEXT("AttributeSet"));

	HealthBar = CreateDefaultSubobject<UWidgetComponent>(TEXT("HealthBar"));
	HealthBar->SetupAttachment(GetRootComponent());
}

void AGASMonster::BeginPlay()
{
	Super::BeginPlay();

	UnHighlightActor();
	InitAbilityActorInfo();

	if (UGASUserWidget* UserWidget = Cast<UGASUserWidget>(HealthBar->GetUserWidgetObject()))
	{
		UserWidget->SetWidgetController(this);
	}

	if (const UGASAttributeSet* AS = Cast<UGASAttributeSet>(AttributeSet))
	{
		AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(AS->GetHealthAttribute()).AddLambda(
			[this](const FOnAttributeChangeData& Data)
			{
				OnHealthChanged.Broadcast(Data.NewValue);
			}
		);

		AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(AS->GetMaxHealthAttribute()).AddLambda(
			[this](const FOnAttributeChangeData& Data)
			{
				OnMaxHealthChanged.Broadcast(Data.NewValue);
			}
		);

		OnHealthChanged.Broadcast(AS->GetHealth());
		OnMaxHealthChanged.Broadcast(AS->GetMaxHealth());
	}
}

void AGASMonster::HighlightActor()
{
	bHighlighted = true;

	GetMesh()->SetRenderCustomDepth(true);
	GetMesh()->SetCustomDepthStencilValue(250);
	
	Weapon->SetRenderCustomDepth(true);
	Weapon->SetCustomDepthStencilValue(250);
}

void AGASMonster::UnHighlightActor()
{
	bHighlighted = false;

	GetMesh()->SetRenderCustomDepth(false);
	Weapon->SetRenderCustomDepth(false);
}

void AGASMonster::InitAbilityActorInfo()
{
	Super::InitAbilityActorInfo();

	AbilitySystemComponent->InitAbilityActorInfo(this, this);
	Cast<UGASAbilitySystemComponent>(AbilitySystemComponent)->OnSetAbilityActorInto();

	InitializeDefaultAttributes();
}
