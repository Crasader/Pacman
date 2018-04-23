#pragma once
#include "TileMap.h"
#include "Ghost.h"
USING_NS_CC;

class TileDoor : public TileMap
{
public:
	virtual bool triggerTile(Ghost* node, Direction direction);
public:
	CREATE_FUNC(TileDoor);
	TileDoor();
	~TileDoor();
};

