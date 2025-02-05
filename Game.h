#pragma once
#include "CoreMinimal.h"

class Game
{
protected:
	RenderWindow window;

public:
	FORCEINLINE virtual bool IsOver() const
	{
		return !window.isOpen();
	}
	FORCEINLINE Vector2f GetWindowSize() const
	{
		return CAST(Vector2f, window.getSize());
	}

public:
	Game();
	virtual ~Game() {};

public:
	virtual void Start();
	virtual bool Update();
	void UpdateWindow();
	virtual void Stop();

	FORCEINLINE Vector2f MapPixelToCoords(const Vector2i& _coords)
	{
		return window.mapPixelToCoords(_coords);
	}

	FORCEINLINE Vector2i MapCoordsToPixel(const Vector2f& _coords)
	{
		return window.mapCoordsToPixel(_coords);
	}
};