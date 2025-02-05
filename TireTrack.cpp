#include "TireTrack.h"

TireTrack::TireTrack(const RectangleShapeData& _data, const string& _name, const float _lifespan) : MeshActor(_data, _name, _lifespan)
{
	opacity = 100;

}



void TireTrack::BeginPlay()
{
	Super::BeginPlay();
}

void TireTrack::Tick(const float _deltaTime)
{
	Super::Tick(_deltaTime);

	opacity -= 2.5;
	GetMesh()->GetShape()->GetDrawable()->setFillColor(Color(123, 63, 0, opacity));

}
