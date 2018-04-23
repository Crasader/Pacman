#include "TileDoor.h"
#include "MapController.h"


bool TileDoor::triggerTile(Ghost * node, Direction direction)
{
	if (TileMap::triggerTile(node, direction)) {
		if (node->getForm() == GhostForm::Door) {
			node->changeForm(GhostForm::Bad);
			node->setTarget(mapController->player);
			node->passedPosition = node->beforeMovingPosition;
			node->isMoving = false;
			return true;
		}
	}
	return false;
}

TileDoor::TileDoor()
{
	this->triggerDirection = Direction::Null;
	this->active = true;
}


TileDoor::~TileDoor()
{
}
