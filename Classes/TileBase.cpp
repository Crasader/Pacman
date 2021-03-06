#include "TileBase.h"
#include "MapController.h"


bool TileBase::triggerTile(Ghost * node, Direction direction)
{
	if (TileMap::triggerTile(node, direction)) {
		if (node->getForm() == GhostForm::Eaten) {
			node->changeForm(GhostForm::Door);
			node->setTarget(mapController->door);
			node->passedPosition = node->beforeMovingPosition;
			node->isMoving = false;
			return true;
		}
	}
	return false;
}

TileBase::TileBase()
{
	this->triggerDirection = Direction::Null;
	this->active = true;
}


TileBase::~TileBase()
{
}
