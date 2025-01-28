#include "Level.h"

void Level::GenerateLevel()
{
	LevelGenerator _generator = LevelGenerator(this, 1600, 1000, 100);

	vector<LevelElement*> _groundVariants;
	_groundVariants.push_back(new LevelElement(new SubclassOf<MeshActor>(new MeshActor(RectangleShapeData({60.f, 60.f }, "Object/Ground_2"))), 0.3f));
	LevelElement* _ground = new LevelElement(new SubclassOf<MeshActor>(new MeshActor(RectangleShapeData({ 60.f, 60.f }, "Object/Ground_1"))), _groundVariants);
	_generator.SetGround(_ground, { 60, 60 });

	vector<LevelElement*> _treeVariants;
	_treeVariants.push_back(new LevelElement(new SubclassOf<MeshActor>(new MeshActor(50.f, 30, "Object/Tree_4")), 1));
	_treeVariants.push_back(new LevelElement(new SubclassOf<MeshActor>(new MeshActor(50.f, 30, "Object/Tree_3")), 1));
	_treeVariants.push_back(new LevelElement(new SubclassOf<MeshActor>(new MeshActor(50.f, 30, "Object/Tree_2")), 1));
	LevelElement* _tree = new LevelElement(new SubclassOf<MeshActor>(new MeshActor(50.f, 30, "Object/Tree_1")), 10, _treeVariants);

	vector<LevelElement*> _rockVariants;
	_rockVariants.push_back(new LevelElement(new SubclassOf<MeshActor>(new MeshActor(50.f, 30, "Object/Rock_1")), 1));
	_rockVariants.push_back(new LevelElement(new SubclassOf<MeshActor>(new MeshActor(50.f, 30, "Object/Rock_2")), 1));
	_rockVariants.push_back(new LevelElement(new SubclassOf<MeshActor>(new MeshActor(50.f, 30, "Object/Rock_3")), 1));
	LevelElement* _rock = new LevelElement(new SubclassOf<MeshActor>(new MeshActor(50.f, 30, "Object/Rock_4")), 10, _rockVariants);

	_generator.AddGenerableElement(_tree);
	_generator.AddGenerableElement(_rock);
	//_generator.AddGenerableElement(new LevelElement(new SubclassOf<MeshActor>(new MeshActor(50.f, 30, "Object/Root_1")), 0.3f));

	_generator.GenerateMap();
}

