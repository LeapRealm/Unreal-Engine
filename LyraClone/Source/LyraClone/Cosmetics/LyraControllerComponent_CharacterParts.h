#pragma once

#include "LyraCharacterPartTypes.h"
#include "Components/ControllerComponent.h"
#include "LyraControllerComponent_CharacterParts.generated.h"

class ULyraPawnComponent_CharacterParts;
// ControllerComponent가 소유하는 Character Part
USTRUCT()
struct FLyraControllerCharacterPartEntry
{
	GENERATED_BODY()

	// Character Part에 대한 메타 데이터(클래스 정보)
	UPROPERTY(EditAnywhere)
	FLyraCharacterPart Part;

	// Controller가 Possess하고 있는 Pawn에서 인스턴스화된 Character Part의 핸들값(고유값)
	FLyraCharacterPartHandle Handle;
};

// Controller가 Pawn을 Possess했을 때, Pawn에 어떤 Cosmetic Actor를 생성할지 결정하는 ControllerComponent
UCLASS(meta=(BlueprintSpawnableComponent))
class ULyraControllerComponent_CharacterParts : public UControllerComponent 
{
	GENERATED_BODY()
	
public:
	ULyraControllerComponent_CharacterParts(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

protected:
	UFUNCTION()
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;
	
public:
	// AddDynamic으로 바인딩하려면 UFUNCTION으로 선언해야한다
	UFUNCTION()
	void OnPossessedPawnChanged(APawn* OldPawn, APawn* NewPawn);
	
	UFUNCTION(BlueprintCallable, Category="Cosmetics")
	void AddCharacterPart(const FLyraCharacterPart& NewPart);
	void AddCharacterPartInternal(const FLyraCharacterPart& NewPart);

	void RemoveAllCharacterParts();

	ULyraPawnComponent_CharacterParts* GetPawnCustomizer() const;
	
public:
	UPROPERTY(EditAnywhere, Category="Cosmetics")
	TArray<FLyraControllerCharacterPartEntry> CharacterParts;
};
