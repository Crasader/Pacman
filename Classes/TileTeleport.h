#pragma once
#include "TileMap.h"
#include "Pacman.h"
#include "Ghost.h"
USING_NS_CC;
class TileTeleport : public TileMap
{
public:
	TileTeleport* linkTile;
public:
	CREATE_FUNC(TileTeleport);
	virtual bool triggerTile(Pacman* node, Direction direction);
	virtual bool triggerTile(Ghost* node, Direction direction);
	virtual void linkTwoSide(TileTeleport* other);
	virtual void linkOneSide(TileTeleport* other);

	TileTeleport();
	~TileTeleport();
};

