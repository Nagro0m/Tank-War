#pragma once
#include "Component.h"

enum CollisionType
{
	CT_NONE,
	CT_OVERLAP,
	CT_BLOCK
};

enum LayerType
{
	LT_WorldDynamic,
	LT_WorldStatic

	// ========= \\


};

/*
* 1 Actor => 1 LayerMask
* 
*/

class CollisionComponent : public Component
{
	LayerType type;
};

