#pragma once
#include "TileMap.h"
#include "cocos2d.h"
#include "Pacman.h"
USING_NS_CC;

class TileBigFood : public TileMap
{
public:
	virtual bool initialize(Sprite* sprite, std::string labelText, MapController* mapController);
	virtual bool triggerTile(Pacman * node, Direction direction);

public:
	CREATE_FUNC(TileBigFood);
	TileBigFood();
	~TileBigFood();
};

