#include "SquareActor.h"

SquareActor::SquareActor(const float& _sideSize, const string& _path, const IntRect& _rect)
	: MeshActor({ _sideSize, _sideSize }, _path, _rect)
{
}
