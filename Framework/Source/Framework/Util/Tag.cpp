#include "Util/Tag.h"

namespace Tag
{

	/* ----------------------------------------------------------------------------------
										Asset Data
	-----------------------------------------------------------------------------------*/
	
	/*--------------------
			Input
	--------------------*/
	UE_DEFINE_GAMEPLAY_TAG(Asset_Input_DefaultMappingContext, "Asset.Input.DefaultMappingContext");
	UE_DEFINE_GAMEPLAY_TAG(Asset_Input_MoveKeyboardAction, "Asset.Input.MoveKeyboardAction");
	UE_DEFINE_GAMEPLAY_TAG(Asset_Input_LeftMouseAction, "Asset.Input.LeftMouseAction");
	UE_DEFINE_GAMEPLAY_TAG(Asset_Input_HoldAction, "Asset.Input.HoldAction");

	/*--------------------
			 Mesh
	--------------------*/
	UE_DEFINE_GAMEPLAY_TAG(Asset_SkeletalMesh_Paladin, "Asset.SkeletalMesh.Paladin");
	UE_DEFINE_GAMEPLAY_TAG(Asset_SkeletalMesh_Skeleton, "Asset.SkeletalMesh.Skeleton");
	
	/*--------------------
		  Animation
	--------------------*/	
	UE_DEFINE_GAMEPLAY_TAG(Asset_AnimBP_Player, "Asset.AnimBP.Player");
	UE_DEFINE_GAMEPLAY_TAG(Asset_Montage_Player_SlashDown, "Asset.Montage.Player.SlashDown");
	UE_DEFINE_GAMEPLAY_TAG(Asset_Montage_Player_SlashUp, "Asset.Montage.Player.SlashUp");
	UE_DEFINE_GAMEPLAY_TAG(Asset_Montage_Player_Dead, "Asset.Montage.Player.Dead");
	
	UE_DEFINE_GAMEPLAY_TAG(Asset_AnimBP_Skeleton, "Asset.AnimBP.Skeleton");
	UE_DEFINE_GAMEPLAY_TAG(Asset_Montage_Skeleton_Dead, "Asset.Montage.Skeleton.Dead");
	UE_DEFINE_GAMEPLAY_TAG(Asset_Montage_Skeleton_Attack, "Asset.Montage.Skeleton.Attack");
	
	/*--------------------
			Effect
	--------------------*/
	UE_DEFINE_GAMEPLAY_TAG(Asset_Effect_Slash, "Asset.Effect.Slash");
	
	/*--------------------
			Widget
	--------------------*/		
	UE_DEFINE_GAMEPLAY_TAG(Asset_Widget_Scene, "Asset.Widget.Scene");
	UE_DEFINE_GAMEPLAY_TAG(Asset_Widget_Nameplate, "Asset.Widget.Nameplate");
	
	/*--------------------
			Skill
	--------------------*/
	UE_DEFINE_GAMEPLAY_TAG(Skill_Slash, "Skill.Slash");
	UE_DEFINE_GAMEPLAY_TAG(Skill_ManaRegen, "Skill.ManaRegen");

	/* ----------------------------------------------------------------------------------
										Game Data
	-----------------------------------------------------------------------------------*/
	
	/*--------------------
			 Stat
	--------------------*/
	UE_DEFINE_GAMEPLAY_TAG(Stat_Health, "Stat.Health");
	UE_DEFINE_GAMEPLAY_TAG(Stat_Mana, "Stat.Mana");
	UE_DEFINE_GAMEPLAY_TAG(Stat_Attack, "Stat.Attack");
	UE_DEFINE_GAMEPLAY_TAG(Stat_Defense, "Stat.Defense");

	/* ----------------------------------------------------------------------------------
										Tag Only
	-----------------------------------------------------------------------------------*/
	
	/*--------------------
			Scene
	--------------------*/
	UE_DEFINE_GAMEPLAY_TAG(Scene_DevMap, "Scene.DevMap");
	
	/*--------------------
		   Creature
	--------------------*/
	UE_DEFINE_GAMEPLAY_TAG(Creature_Player, "Creature.Player");
	UE_DEFINE_GAMEPLAY_TAG(Creature_Skeleton, "Creature.Skeleton");
}
