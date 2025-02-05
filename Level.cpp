#include "Level.h"
#include "CollisionComponent.h"
#include "Root.h"
#include "Rock.h"
#include "Grass.h"
#include "Tree.h"


void Level::GenerateLevel()
{
	LevelGenerator _generator = LevelGenerator(this, 3840, 2160, 106);
	//LevelGenerator _generator = LevelGenerator(this, 1920, 1080, 106);

	vector<LevelElement*> _groundVariants;
	LevelElement* _ground = new LevelElement(new MeshActor(RectangleShapeData({ 180.0f, 180.0f }, "Object/Grounds_3")), _groundVariants);
	_generator.SetGround(_ground, { 120, 120 });

	vector<LevelElement*> _treeVariants;
	const Vector2f& _size = Vector2f(80.0f, 80.0f);
	_treeVariants.push_back(new LevelElement(new Tree(RectangleShapeData(_size, "Object/Tree_4")), 2));
	_treeVariants.push_back(new LevelElement(new Tree(RectangleShapeData(_size, "Object/Tree_3")), 2));
	_treeVariants.push_back(new LevelElement(new Tree(RectangleShapeData(_size, "Object/Tree_2")), 2));
	LevelElement* _tree = new LevelElement(new Tree(RectangleShapeData(_size, "Object/Tree_1")), 10, _treeVariants);

	vector<pair<string, CollisionType>> _responsesMesh = { { "Tank", CT_OVERLAP } };
	_tree->AddCollision(_responsesMesh, "Tree");

	vector<LevelElement*> _grassVariants;
	const Vector2f& _grassSize = Vector2f(30.0f, 30.0f);
	_grassVariants.push_back(new LevelElement(new Grass(RectangleShapeData(_grassSize, "Object/Grass_2")), 2));
	LevelElement* _grass = new LevelElement(new Grass(RectangleShapeData(_grassSize, "Object/Grass_1")), 5, _grassVariants);
			
	_grass->AddCollision(_responsesMesh, "Grass");

	vector<LevelElement*> _rootVariants;
	const Vector2f& _rootSize = Vector2f(50.0f, 30.0f);
	_rootVariants.push_back(new LevelElement(new Root(RectangleShapeData(_rootSize, "Object/Root_2")), 2));
	LevelElement* _root = new LevelElement(new Root(RectangleShapeData(_rootSize, "Object/Root_1")), 1, _rootVariants);

	_root->AddCollision(_responsesMesh, "Root");

	vector<LevelElement*> _rockVariants;
	const Vector2f& _rockSize = Vector2f(50.0f, 40.0f);
	_rockVariants.push_back(new LevelElement(new Rock(RectangleShapeData(_rockSize, "Object/Rock_1")), 1));
	_rockVariants.push_back(new LevelElement(new Rock(RectangleShapeData(_rockSize, "Object/Rock_2")), 1));
	_rockVariants.push_back(new LevelElement(new Rock(RectangleShapeData(_rockSize, "Object/Rock_3")), 1));
	LevelElement* _rock = new LevelElement(new Rock(RectangleShapeData(_rockSize, "Object/Rock_4")), 3, _rockVariants);

	_rock->AddCollision(_responsesMesh, "Rock");

	_generator.AddGenerableElement(_tree);
	_generator.AddGenerableElement(_rock);
	_generator.AddGenerableElement(_grass);
	_generator.AddGenerableElement(_root);

	_generator.GenerateMap();
}

Level::~Level()
{
}