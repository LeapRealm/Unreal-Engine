#pragma once

#include "CoreMinimal.h"
#include "NativeGameplayTags.h"

namespace Tag
{
	/* ----------------------------------------------------------------------------------
										Asset Data
	-----------------------------------------------------------------------------------*/

	/*--------------------
		    Input
	--------------------*/
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(Asset_Input_DefaultMappingContext);
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(Asset_Input_MoveKeyboardAction);
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(Asset_Input_LeftMouseAction);
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(Asset_Input_HoldAction);
	
	/*--------------------
			 Mesh
	--------------------*/
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(Asset_SkeletalMesh_Paladin);
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(Asset_SkeletalMesh_Skeleton);
	
	/*--------------------
		  Animation
	--------------------*/
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(Asset_AnimBP_Player);
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(Asset_Montage_Player_SlashDown);
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(Asset_Montage_Player_SlashUp);
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(Asset_Montage_Player_Dead);
	
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(Asset_AnimBP_Skeleton);
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(Asset_Montage_Skeleton_Attack);
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(Asset_Montage_Skeleton_Dead);

	/*--------------------
			Effect
	--------------------*/
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(Asset_Effect_Slash);
	
	/*--------------------
			Widget
	--------------------*/	
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(Asset_Widget_Scene);
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(Asset_Widget_Nameplate);

	/*--------------------
			Skill
	--------------------*/
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(Skill_Slash);
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(Skill_ManaRegen);

	/* ----------------------------------------------------------------------------------
										Game Data
	-----------------------------------------------------------------------------------*/
	
	/*--------------------
    		 Stat
    --------------------*/
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(Stat_Health);
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(Stat_Mana);
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(Stat_Attack);
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(Stat_Defense);

	/* ----------------------------------------------------------------------------------
										Tag Only
	-----------------------------------------------------------------------------------*/

	/*--------------------
			Scene
	--------------------*/
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(Scene_DevMap);
	
	/*--------------------
		   Creature
	--------------------*/
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(Creature_Player);
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(Creature_Skeleton);
}
