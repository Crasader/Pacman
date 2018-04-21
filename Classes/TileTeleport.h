#pragma once
#include "TileMap.h"
USING_NS_CC;
class TileTeleport : public TileMap
{
public:
	TileTeleport* linkTile;
public:
	CREATE_FUNC(TileTeleport);
	virtual bool triggerTile(Node* node, Direction direction);
	virtual void linkTwoSide(TileTeleport* other);
	virtual void linkOneSide(TileTeleport* other);

	TileTeleport();
	~TileTeleport();
};

