#include "Level.h"
#include "CollisionComponent.h"
#include "Root.h"
#include "Rock.h"
#include "Grass.h"
#include "Tree.h"


void Level::GenerateLevel()
{
    LevelGenerator _generator(this, 3840, 2160, 106);

    // Ground element (idem dans les deux codes)
    vector<LevelElement<MeshActor>*> _groundVariants;
    LevelElement<MeshActor>* _ground = new LevelElement<MeshActor>(new MeshActor(RectangleShapeData({ 180.0f, 180.0f }, "Object/Grounds_3")), _groundVariants);
    _generator.SetGround(_ground, { 120, 120 });

    // Tree elements with variants (adapté à partir de l'ancien code)
    vector<LevelElement<MeshActor>*> _treeVariants;
    const Vector2f _size(80.0f, 80.0f);  // Taille pour les arbres
    _treeVariants.push_back(new LevelElement<MeshActor>(new Tree(RectangleShapeData(_size, "Object/Tree_4")), 2));
    _treeVariants.push_back(new LevelElement<MeshActor>(new Tree(RectangleShapeData(_size, "Object/Tree_3")), 2));
    _treeVariants.push_back(new LevelElement<MeshActor>(new Tree(RectangleShapeData(_size, "Object/Tree_2")), 2));
    LevelElement<MeshActor>* _tree = new LevelElement<MeshActor>(new Tree(RectangleShapeData(_size, "Object/Tree_1")), 10, _treeVariants);

    // Grass elements with variants (adapté à partir de l'ancien code)
    vector<LevelElement<MeshActor>*> _grassVariants;
    const Vector2f _grassSize(30.0f, 30.0f);  // Taille pour l'herbe
    _grassVariants.push_back(new LevelElement<MeshActor>(new Grass(RectangleShapeData(_grassSize, "Object/Grass_2")), 2));
    LevelElement<MeshActor>* _grass = new LevelElement<MeshActor>(new Grass(RectangleShapeData(_grassSize, "Object/Grass_1")), 5, _grassVariants);

    // Root elements with variants (adapté à partir de l'ancien code)
    vector<LevelElement<MeshActor>*> _rootVariants;
    const Vector2f _rootSize(50.0f, 30.0f);  // Taille pour les racines
    _rootVariants.push_back(new LevelElement<MeshActor>(new Root(RectangleShapeData(_rootSize, "Object/Root_2")), 2));
    LevelElement<MeshActor>* _root = new LevelElement<MeshActor>(new Root(RectangleShapeData(_rootSize, "Object/Root_1")), 1, _rootVariants);

    // Rock elements with variants (adapté à partir de l'ancien code)
    vector<LevelElement<MeshActor>*> _rockVariants;
    const Vector2f _rockSize(50.0f, 40.0f);  // Taille pour les rochers
    _rockVariants.push_back(new LevelElement<MeshActor>(new Rock(RectangleShapeData(_rockSize, "Object/Rock_1")), 1));
    _rockVariants.push_back(new LevelElement<MeshActor>(new Rock(RectangleShapeData(_rockSize, "Object/Rock_2")), 1));
    _rockVariants.push_back(new LevelElement<MeshActor>(new Rock(RectangleShapeData(_rockSize, "Object/Rock_3")), 1));
    LevelElement<MeshActor>* _rock = new LevelElement<MeshActor>(new Rock(RectangleShapeData(_rockSize, "Object/Rock_4")), 3, _rockVariants);

    // Ajouter tous les éléments générables
    _generator.AddGenerableElement(_tree);
    _generator.AddGenerableElement(_rock);
    _generator.AddGenerableElement(_grass);
    _generator.AddGenerableElement(_root);

    // Générer la carte
    _generator.GenerateMap();
}


Level::~Level()
{

}