#pragma once

#include "LyraClone/Cosmetics/LyraCosmeticAnimationTypes.h"
#include "LyraClone/Equipment/LyraEquipmentInstance.h"
#include "LyraWeaponInstance.generated.h"

UCLASS()
class ULyraWeaponInstance : public  ULyraEquipmentInstance
{
	GENERATED_BODY()
	
public:
	ULyraWeaponInstance(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Animation")
	FLyraAnimLayerSelectionSet EquippedAnimSet;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Animation")
	FLyraAnimLayerSelectionSet UnequippedAnimSet;
};
