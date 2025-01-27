#include "Level.h"

void Level::GenerateLevel()
{
	LevelGenerator _generator = LevelGenerator(this, 1600, 1600, 100);

	vector<LevelElement*> _groundVariants;
	_groundVariants.push_back(new LevelElement(new SubclassOf<MeshActor>(new MeshActor(RectangleShapeData({60.f, 60.f }, "Object/Ground_2"))), 0.3f));
	LevelElement* _ground = new LevelElement(new SubclassOf<MeshActor>(new MeshActor(RectangleShapeData({ 60.f, 60.f }, "Object/Ground_1"))), _groundVariants);
	_generator.SetGround(_ground, { 60, 60 });

	vector<LevelElement*> _treeVariants;
	_treeVariants.push_back(new LevelElement(new SubclassOf<MeshActor>(new MeshActor(50.f, 30, "Object/Tree_4")), 0.5f));
	LevelElement* _tree = new LevelElement(new SubclassOf<MeshActor>(new MeshActor(50.f, 30, "Object/Tree_1")), 0.5f, _treeVariants);

	_generator.AddGenerableElement(_tree);
	//_generator.AddGenerableElement(new LevelElement(new SubclassOf<MeshActor>(new MeshActor(50.f, 30, "Object/Root_1")), 0.3f));

	_generator.GenerateMap();
}

