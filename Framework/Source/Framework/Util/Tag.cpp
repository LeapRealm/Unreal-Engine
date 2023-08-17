#include "Util/Tag.h"

namespace Tag
{
	/*--------------------
		    Scene
	--------------------*/
	UE_DEFINE_GAMEPLAY_TAG(Scene_DevMap, "Scene.DevMap");

	/*--------------------
			Asset
	--------------------*/
	UE_DEFINE_GAMEPLAY_TAG(Asset_Input_DefaultMappingContext, "Asset.Input.DefaultMappingContext");
	UE_DEFINE_GAMEPLAY_TAG(Asset_Input_MoveKeyboardAction, "Asset.Input.MoveKeyboardAction");
	UE_DEFINE_GAMEPLAY_TAG(Asset_Input_LeftMouseAction, "Asset.Input.LeftMouseAction");
	UE_DEFINE_GAMEPLAY_TAG(Asset_Input_HoldAction, "Asset.Input.HoldAction");
	
	UE_DEFINE_GAMEPLAY_TAG(Asset_SkeletalMesh_Player, "Asset.SkeletalMesh.Player");
	UE_DEFINE_GAMEPLAY_TAG(Asset_AnimBP_Player, "Asset.AnimBP.Player");
	
	UE_DEFINE_GAMEPLAY_TAG(Asset_SkeletalMesh_Skeleton, "Asset.SkeletalMesh.Skeleton");
	UE_DEFINE_GAMEPLAY_TAG(Asset_AnimBP_Skeleton, "Asset.AnimBP.Skeleton");
	
	UE_DEFINE_GAMEPLAY_TAG(Asset_Widget_Nameplate, "Asset.Widget.Nameplate");
	
	/*--------------------
			Skill
	--------------------*/
	UE_DEFINE_GAMEPLAY_TAG(Skill_Slash, "Skill.Slash");
	UE_DEFINE_GAMEPLAY_TAG(Asset_Montage_SlashDown, "Asset.Montage.SlashDown");
	UE_DEFINE_GAMEPLAY_TAG(Asset_Montage_SlashUp, "Asset.Montage.SlashUp");
	UE_DEFINE_GAMEPLAY_TAG(Asset_Effect_Slash, "Asset.Effect.Slash");
	UE_DEFINE_GAMEPLAY_TAG(Asset_Effect_SlashImpact, "Asset.Effect.SlashImpact");

	/*--------------------
			 Stat
	--------------------*/
	UE_DEFINE_GAMEPLAY_TAG(Stat_Health, "Stat.Health");
	UE_DEFINE_GAMEPLAY_TAG(Stat_Mana, "Stat.Mana");
	UE_DEFINE_GAMEPLAY_TAG(Stat_Attack, "Stat.Attack");
	UE_DEFINE_GAMEPLAY_TAG(Stat_Defense, "Stat.Defense");

	/*--------------------
		   Creature
	--------------------*/
	UE_DEFINE_GAMEPLAY_TAG(Creature_Player, "Creature.Player");
	UE_DEFINE_GAMEPLAY_TAG(Creature_Skeleton, "Creature.Skeleton");
}
