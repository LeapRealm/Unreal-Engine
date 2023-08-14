#include "Util/Tag.h"

namespace Tag
{
	/*--------------------
		    Scene
	--------------------*/
	UE_DEFINE_GAMEPLAY_TAG(Scene_DevMap, "Scene.DevMap");

	/*--------------------
	       Resource
	--------------------*/
	UE_DEFINE_GAMEPLAY_TAG(Asset_Input_DefaultMappingContext, "Asset.Input.DefaultMappingContext");
	UE_DEFINE_GAMEPLAY_TAG(Asset_Input_MoveKeyboardAction, "Asset.Input.MoveKeyboardAction");
	UE_DEFINE_GAMEPLAY_TAG(Asset_Input_MoveMouseAction, "Asset.Input.MoveMouseAction");
	UE_DEFINE_GAMEPLAY_TAG(Asset_Input_HoldAction, "Asset.Input.HoldAction");
	
	UE_DEFINE_GAMEPLAY_TAG(Asset_SkeletalMesh_Player, "Asset.SkeletalMesh.Player");
	UE_DEFINE_GAMEPLAY_TAG(Asset_AnimBP_Player, "Asset.AnimBP.Player");
}
