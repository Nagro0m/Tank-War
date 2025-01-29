#pragma once
#include "MeshActor.h"
#include "SubclassOf.h"



struct HullsData
{
	vector<string> _hullsName;
	map<string, SubclassOf<MeshActor>> _hulls;

	HullsData()
	{
		_hullsName =
		{
			"1",
			"2",
			"3",
			"4",
		};
	}
};


class TankEditor
{
	HullsData _hullsData;
	//map<string, SubclassOf<MeshActor*>> _weapons;
	//map<string, SubclassOf<MeshActor*>> _tracks;

public:
	TankEditor();
	~TankEditor();

public:
	void InitHullsData();
};

