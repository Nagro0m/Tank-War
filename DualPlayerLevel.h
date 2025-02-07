#pragma once
#include "Level.h"
#include "LevelGenerator.h"

class DualPlayerLevel : public Level
{

public:

public:
	virtual void Load() override;
	virtual void Unload() override;

protected:
	virtual void InitLevel() override;

private:
	void GenerateLevel();
};

