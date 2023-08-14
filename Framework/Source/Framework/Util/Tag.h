#pragma once

#include "CoreMinimal.h"
#include "NativeGameplayTags.h"

namespace Tag
{
	/*--------------------
	        Scene
	--------------------*/
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(Scene_DevMap);

	/*--------------------
		   Resource
	--------------------*/
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(Asset_Input_DefaultMappingContext);
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(Asset_Input_MoveKeyboardAction);
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(Asset_Input_MoveMouseAction);
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(Asset_Input_HoldAction);
	
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(Asset_SkeletalMesh_Player);
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(Asset_AnimBP_Player);
}
