#include "TileMap.h"



bool TileMap::triggerTile(Node * node, Direction direction)
{
	return (
		this->active &&
		this->getPosition() == node->getPosition() &&  
		(this->triggerDirection == Direction::Null || this->triggerDirection == direction)
	);
}

void TileMap::activate(bool active)
{
	this->active = active;
}

TileMap::TileMap()
{
	this->triggerDirection = Direction::Null;
	this->active = true;
}


TileMap::~TileMap()
{
}
