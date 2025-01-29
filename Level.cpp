#include "Level.h"

void Level::GenerateLevel()
{
	LevelGenerator _generator = LevelGenerator(this, 5760, 3240, 106);

	vector<LevelElement*> _groundVariants;
	LevelElement* _ground = new LevelElement(new MeshActor(RectangleShapeData({ 180.0f, 180.0f }, "Object/Grounds_3")), _groundVariants);
	_generator.SetGround(_ground, { 120, 120 });

	vector<LevelElement*> _treeVariants;
	const Vector2f& _size = Vector2f(80.0f, 80.0f);
	_treeVariants.push_back(new LevelElement(new MeshActor(RectangleShapeData(_size, "Object/Tree_4")), 2));
	_treeVariants.push_back(new LevelElement(new MeshActor(RectangleShapeData(_size, "Object/Tree_3")), 2));
	_treeVariants.push_back(new LevelElement(new MeshActor(RectangleShapeData(_size, "Object/Tree_2")), 2));
	LevelElement* _tree = new LevelElement(new MeshActor(RectangleShapeData(_size, "Object/Tree_1")), 5, _treeVariants);

	//vector<LevelElement*> _grassVariants;
	//const Vector2f& _grassSize = Vector2f(20.0f, 20.0f);
	//_grassVariants.push_back(new LevelElement(new MeshActor(RectangleShapeData(_grassSize, "Object/Grass_2")), 2));
	//LevelElement* _grass = new LevelElement(new MeshActor(RectangleShapeData(_grassSize, "Object/Grass_1")), 3, _grassVariants);


	vector<LevelElement*> _rockVariants;
	const Vector2f& _rockSize = Vector2f(50.0f, 50.0f);
	_rockVariants.push_back(new LevelElement(new MeshActor(RectangleShapeData(_rockSize, "Object/Rock_1")), 1));
	_rockVariants.push_back(new LevelElement(new MeshActor(RectangleShapeData(_rockSize, "Object/Rock_2")), 1));
	_rockVariants.push_back(new LevelElement(new MeshActor(RectangleShapeData(_rockSize, "Object/Rock_3")), 1));
	_rockVariants.push_back(new LevelElement(new MeshActor(RectangleShapeData(_rockSize, "Object/Grass_1")), 1));
	LevelElement* _rock = new LevelElement(new MeshActor(RectangleShapeData(_rockSize, "Object/Rock_4")), 15, _rockVariants);

	_generator.AddGenerableElement(_tree);
	_generator.AddGenerableElement(_rock);
	//_generator.AddGenerableElement(_grass);
	//_generator.AddGenerableElement(new LevelElement(new SubclassOf<MeshActor>(new MeshActor(50.0f, 30, "Object/Root_1")), 0.3f));

	_generator.GenerateMap();
}

Level::~Level()
{
}