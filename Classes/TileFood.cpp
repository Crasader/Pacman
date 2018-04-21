#include "TileFood.h"
#include "MapController.h"


bool TileFood::triggerTile(Node * node, Direction direction)
{
	if (TileMap::triggerTile(node, direction)) {
		//mapController->removeChild(this, true);
		mapController->reduceFoodCount();
		this->sprite->setColor(Color3B(0, 0, 0));
		this->activate(false);
		return true;
	}
	return false;
}

TileFood::TileFood()
{
}


TileFood::~TileFood()
{
}
