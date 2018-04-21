#pragma once
#include "StaticObject.h"
#include "cocos2d.h"
#include "Enum.h"

USING_NS_CC;

class MapController;

class TileMap :	public StaticObject
{
protected:
	bool active;
public:
	Direction triggerDirection;
public:
	CREATE_FUNC(TileMap);
	virtual bool triggerTile(Node* node, Direction direction);
	virtual void activate(bool active);
public:
	TileMap();
	~TileMap();
};

