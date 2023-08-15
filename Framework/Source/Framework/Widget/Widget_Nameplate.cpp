#include "Widget/Widget_Nameplate.h"

#include "Components/ProgressBar.h"
#include "Data/GameData.h"
#include "Kismet/KismetMathLibrary.h"
#include "Util/Tag.h"

void UWidget_Nameplate::RefreshUI(const FGameplayTag& StatTag, const FStatData& StatData)
{
	Super::RefreshUI(StatTag, StatData);

	if (StatTag == Tag::Stat_Health)
	{
		float Percent = UKismetMathLibrary::SafeDivide(StatData.Value, StatData.MaxValue);
		HealthBar->SetPercent(Percent);
	}
}
