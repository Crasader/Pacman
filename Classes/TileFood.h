#pragma once
#include "TileMap.h"
#include "cocos2d.h"
#include "Pacman.h"
USING_NS_CC;

class TileFood : public TileMap
{
public:
	virtual bool triggerTile(Pacman * node, Direction direction);
	
public:
	CREATE_FUNC(TileFood);
	TileFood();
	~TileFood();
};

