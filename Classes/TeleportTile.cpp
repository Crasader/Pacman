#include "TeleportTile.h"



bool TeleportTile::trigger(MovableObject::Direction direction, Node* object)
{
	if (this->triggerDirection == direction) {
		object->setPosition(linkTile->getPosition());
		return true;
	}
	return false;
}

void TeleportTile::linkTwoSide(TeleportTile * other)
{
	this->linkOneSide(other);
	other->linkOneSide(this);
}

void TeleportTile::linkOneSide(TeleportTile * other)
{
	this->linkTile = other;
}

TeleportTile::TeleportTile()
{
}


TeleportTile::~TeleportTile()
{
}
