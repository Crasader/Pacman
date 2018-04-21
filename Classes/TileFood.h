#pragma once
#include "TileMap.h"
#include "cocos2d.h"
USING_NS_CC;

class TileFood : public TileMap
{
public:
	virtual bool triggerTile(MovableObject * node, Direction direction);
	
public:
	CREATE_FUNC(TileFood);
	TileFood();
	~TileFood();
};

