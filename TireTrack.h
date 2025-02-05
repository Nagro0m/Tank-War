#pragma once
#include "MeshActor.h"

class TireTrack : public MeshActor
{
	float opacity;

public:
	TireTrack(const RectangleShapeData& _data, const string& _name = "MeshActor", const float _lifespan = 0.0f);


public:
	virtual void BeginPlay() override;
	virtual void Tick(const float _deltaTime) override;

};

