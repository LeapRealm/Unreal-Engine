#include "Widget/Scene/Widget_Scene.h"

#include "Components/ProgressBar.h"
#include "Data/GameData.h"
#include "Kismet/KismetMathLibrary.h"
#include "Util/Tag.h"

void UWidget_Scene::RefreshUI(const FGameplayTag& StatTag, const FStatData& StatData)
{
	Super::RefreshUI(StatTag, StatData);

	if (StatTag == Tag::Stat_Health)
	{
		HealthBar->SetPercent(UKismetMathLibrary::SafeDivide(StatData.Value,StatData.MaxValue));
	}
	else if (StatTag == Tag::Stat_Mana)
	{
		ManaBar->SetPercent(UKismetMathLibrary::SafeDivide(StatData.Value,StatData.MaxValue));
	}
}
