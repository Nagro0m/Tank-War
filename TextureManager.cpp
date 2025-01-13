#include "TextureManager.h"

TextureManager::TextureManager()
{
	defaultTexturePath = "DefaultTexture";
	defaultExtension = "png";
	defaultTexture = nullptr;
}

TextureManager::~TextureManager()
{
	delete defaultTexture;
}

void TextureManager::LoadDefaultTexture()
{
	const string& _finalPath = defaultTexturePath + "." + defaultExtension;
	defaultTexture = new Texture();
	LoadTexture(*defaultTexture, _finalPath);
}

void TextureManager::LoadTexture(Texture& _texture, const string& _path, const IntRect _rect)
{
	const string& _finalPath = "Assets/Textures/" + _path;
	if (!_texture.loadFromFile(_finalPath, false, _rect))
	{
		cerr << "Error => Cannot open file with the following path : '" + _finalPath + "' !";
		_texture = GetDefaultTexture();
	}
}

void TextureManager::SetTexture(ShapeObject* _shape, const Texture* _texture)
{
	_shape->GetDrawable()->setTexture(_texture);
}

void TextureManager::Load(ShapeObject* _shape, const string& _path,
						  const IntRect _rect, const bool _isRepeated, const bool _smooth)
{
	Texture& _texture = _shape->GetTexture();
	if (_path.empty())
	{
		cerr << "Error => Cannot open file with an empty path" << endl;
		_texture = GetDefaultTexture();
	}
	//Init Texture
	LoadTexture(_texture, _path, _rect);
	_texture.setRepeated(_isRepeated);
	_texture.setSmooth(_smooth);

	//Apply Texture
	SetTexture(_shape, &_texture);
}