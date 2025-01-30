#include "TankPart.h"


Tank::TankPart::TankPart(const TankPartType& _type, 
	const RectangleShapeData& _rectangleShapeData)
	: MeshActor(_rectangleShapeData, "TankPart")
{
	partType = _type;

}