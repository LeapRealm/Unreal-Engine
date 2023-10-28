#include "AuraUserWidget.h"

#include "Character/AuraCharacter.h"
#include "Player/AuraPlayerController.h"
#include "Player/AuraPlayerState.h"

#include UE_INLINE_GENERATED_CPP_BY_NAME(AuraUserWidget)

UAuraUserWidget::UAuraUserWidget(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
    
}

void UAuraUserWidget::NativeConstruct()
{
	Super::NativeConstruct();

	PlayerController = Cast<AAuraPlayerController>(GetOwningPlayer());
	check(PlayerController);
	
	PlayerState = GetOwningPlayerState<AAuraPlayerState>();
	check(PlayerState);
	
	AAuraCharacter* AuraCharacter = Cast<AAuraCharacter>(GetOwningPlayerPawn());
	check(AuraCharacter);

	AbilitySystemComponent = AuraCharacter->GetAbilitySystemComponent();
	check(AbilitySystemComponent);

	AttributeSet = AuraCharacter->GetAttributeSet();
	check(AttributeSet);
}
