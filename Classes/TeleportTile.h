#pragma once
#include "StaticObject.h"
#include "MovableObject.h"

USING_NS_CC;

class TeleportTile : public StaticObject
{
public:
	TeleportTile* linkTile;
	Direction triggerDirection;
public:
	CREATE_FUNC(TeleportTile);
	bool trigger(Direction direction, Node* object);

	void linkTwoSide(TeleportTile* other);
	void linkOneSide(TeleportTile* other);

	TeleportTile();
	~TeleportTile();
};

