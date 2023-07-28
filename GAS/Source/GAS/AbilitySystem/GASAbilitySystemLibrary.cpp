#include "GASAbilitySystemLibrary.h"

#include "GASHUD.h"
#include "GASPlayerState.h"
#include "GASWidgetController.h"
#include "Kismet/GameplayStatics.h"

UOverlayWidgetController* UGASAbilitySystemLibrary::GetOverlayWidgetController(const UObject* WorldObjectContext)
{
	if (APlayerController* PC = UGameplayStatics::GetPlayerController(WorldObjectContext, 0))
	{
		if (AGASHUD* GASHUD = Cast<AGASHUD>(PC->GetHUD()))
		{
			AGASPlayerState* PS = PC->GetPlayerState<AGASPlayerState>();
			UAbilitySystemComponent* ASC = PS->GetAbilitySystemComponent();
			UAttributeSet* AS = PS->GetAttributeSet();

			const FWidgetControllerParams WidgetControllerParams(PC, PS, ASC, AS);
			return GASHUD->GetOverlayWidgetController(WidgetControllerParams);
		}
	}

	return nullptr;
}

UAttributeMenuWidgetController* UGASAbilitySystemLibrary::GetAttributeMenuWidgetController(const UObject* WorldObjectContext)
{
	if (APlayerController* PC = UGameplayStatics::GetPlayerController(WorldObjectContext, 0))
	{
		if (AGASHUD* GASHUD = Cast<AGASHUD>(PC->GetHUD()))
		{
			AGASPlayerState* PS = PC->GetPlayerState<AGASPlayerState>();
			UAbilitySystemComponent* ASC = PS->GetAbilitySystemComponent();
			UAttributeSet* AS = PS->GetAttributeSet();

			const FWidgetControllerParams WidgetControllerParams(PC, PS, ASC, AS);
			return GASHUD->GetAttributeMenuWidgetController(WidgetControllerParams);
		}
	}

	return nullptr;
}
