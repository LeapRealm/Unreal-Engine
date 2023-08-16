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
		    Asset
	--------------------*/
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(Asset_Input_DefaultMappingContext);
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(Asset_Input_MoveKeyboardAction);
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(Asset_Input_LeftMouseAction);
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(Asset_Input_HoldAction);
	
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(Asset_SkeletalMesh_Player);
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(Asset_AnimBP_Player);
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(Asset_Montage_PlayerSlash);
	
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(Asset_SkeletalMesh_Skeleton);
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(Asset_AnimBP_Skeleton);
	
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(Asset_Widget_Nameplate);

	/*--------------------
			Skill
	--------------------*/
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(Skill_Slash);
	
	/*--------------------
    		 Stat
    --------------------*/
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(Stat_Health);
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(Stat_Mana);
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(Stat_Attack);
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(Stat_Defense);
	
	/*--------------------
		   Creature
	--------------------*/
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(Creature_Player);
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(Creature_Skeleton);
}
