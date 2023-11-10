#include "CharacterClassInfo.h"

#include UE_INLINE_GENERATED_CPP_BY_NAME(CharacterClassInfo)

UCharacterClassInfo::UCharacterClassInfo(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
    
}

FCharacterClassDefaultInfo UCharacterClassInfo::GetClassDefaultInfo(ECharacterClass CharacterClass)
{
	return CharacterClassInfos.FindChecked(CharacterClass);
}
