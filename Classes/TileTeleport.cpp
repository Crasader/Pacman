#include "TileTeleport.h"


bool TileTeleport::triggerTile(MovableObject * node, Direction direction)
{
	if (TileMap::triggerTile(node, direction)) {
		node->setPosition(linkTile->getPosition());
		node->beforeMovingPosition = node->getPosition();
		return true;
	}
	return false;
}

void TileTeleport::linkTwoSide(TileTeleport * other)
{
	this->linkOneSide(other);
	other->linkOneSide(this);
}

void TileTeleport::linkOneSide(TileTeleport * other)
{
	this->linkTile = other;
}

TileTeleport::TileTeleport() : TileMap()
{
	this->active = true;
}


TileTeleport::~TileTeleport()
{
}
