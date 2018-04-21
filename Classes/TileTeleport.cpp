#include "TileTeleport.h"


bool TileTeleport::triggerTile(Node * node, Direction direction)
{
	if (TileMap::triggerTile(node, direction)) {
		node->setPosition(linkTile->getPosition());
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

TileTeleport::TileTeleport()
{
}


TileTeleport::~TileTeleport()
{
}
