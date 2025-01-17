#pragma once
#include "Singleton.h"
#include "ShapeObject.h"

class TextureManager : public Singleton<TextureManager>
{
	string defaultTexturePath;
	string defaultTextureExtension;
	Texture* defaultTexture;

private:
	// Lazy pointeur
	FORCEINLINE Texture GetDefaultTexture()
	{
		if (!defaultTexture)
		{
			LoadDefaultTexture();
		}

		return *defaultTexture;
	}

public:
	TextureManager();
	~TextureManager();
public:
	/// <summary>
	/// Modifier un shape à partir d'un path
	/// </summary>
	/// <param name="_shape"></param>
	/// <param name="_path"></param>
	/// <param name="_isRepeated"></param>
	/// <param name="_smooth"></param>
	void Load(ShapeObject* _shape, const string& _path,
		 const IntRect& _rect = IntRect(), const bool _isRepeated = false, const bool _smooth = false);

private :
	void LoadTexture(Texture& _texture, const string& _path, const IntRect& _rect = IntRect());
	void LoadDefaultTexture();
	void SetTexture(Shape* _shape, const Texture* _texture);
};

