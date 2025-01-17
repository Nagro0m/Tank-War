#include "TextureManager.h"


TextureManager::TextureManager()
{
	defaultTexturePath = "MissingTexture";
	defaultTextureExtension = ".png";
	defaultTexture = nullptr;
}

TextureManager::~TextureManager()
{
	delete defaultTexture;
}

void TextureManager::Load(ShapeObject* _shape, const string& _path,
	const IntRect& _rect, const bool _isRepeated, const bool _smooth)
{
	Texture& _texture = _shape->GetTexture();
	if (_path.empty())
	{
		LOG(Error, "Cannot open file with empty path");
		_texture = GetDefaultTexture();
		SetTexture(_shape->GetDrawable(), &_texture);
		return;
	}
	LoadTexture(_texture, _path, _rect);
	_texture.setRepeated(_isRepeated);
	_texture.setSmooth(_smooth);
	SetTexture(_shape->GetDrawable(), &_texture);
}

void TextureManager::LoadTexture(Texture& _texture, const string& _path, const IntRect& _rect)
{
	const string& _finalPath = "Assets/Textures/" + _path + defaultTextureExtension;
	if (!_texture.loadFromFile(_finalPath, false, _rect))
	{
		LOG(Error, "Cannot open file with path : \'" + _finalPath + "\'");
		_texture = GetDefaultTexture();
	}
}

void TextureManager::LoadDefaultTexture()
{
	defaultTexture =  new Texture();
	LoadTexture(*defaultTexture, defaultTexturePath);
}

void TextureManager::SetTexture(Shape* _shape, const Texture* _texture)
{
	_shape->setTexture(_texture);
}


