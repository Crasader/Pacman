#include "TileMap.h"
#include "MovableObject.h"


bool TileMap::triggerTile(MovableObject * node, Direction direction)
{
	return (
		this->active &&
		this->getPosition() == node->getPosition() &&  
		(this->triggerDirection == Direction::Null || this->triggerDirection == direction)
	);
}

bool TileMap::triggerTile(Pacman * node, Direction direction)
{
	return triggerTile((MovableObject*)node, direction);
}

bool TileMap::triggerTile(Ghost * node, Direction direction)
{
	return triggerTile((MovableObject*)node, direction);
}

void TileMap::activate(bool active)
{
	this->active = active;
}

TileMap::TileMap()
{
	this->triggerDirection = Direction::Null;
	this->active = false;
}


TileMap::~TileMap()
{
}
