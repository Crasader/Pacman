#pragma once
#include "StaticObject.h"
#include "cocos2d.h"
#include "Enum.h"
#include "MovableObject.h"
#include "Pacman.h"
#include "Ghost.h"
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
	virtual bool triggerTile(MovableObject* node, Direction direction);
	virtual bool triggerTile(Pacman* node, Direction direction);
	virtual bool triggerTile(Ghost* node, Direction direction);
	virtual void activate(bool active);
public:
	TileMap();
	~TileMap();
};

