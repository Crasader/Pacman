#include "TileFood.h"
#include "MapController.h"


bool TileFood::triggerTile(MovableObject * node, Direction direction)
{
	if (TileMap::triggerTile(node, direction)) {
		mapController->reduceFoodCount();
		this->sprite->setColor(Color3B(0, 0, 0));
		this->activate(false);
		return true;
	}
	return false;
}

TileFood::TileFood() : TileMap()
{
	this->active = true;
}


TileFood::~TileFood()
{
}
