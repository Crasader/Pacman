#include "Ghost.h"
#include "MapController.h"
#include "TeleportTile.h"

void Ghost::setTarget(StaticObject * target)
{
	this->target = target;
}

void Ghost::setMapController(MapController * mapController)
{
	this->mapController = mapController;
}

void Ghost::move(float deltaTime)
{
	if (target == nullptr) {
		return;
	}

	if (mapController->positionToChar(beforeMovingPosition) == 'T') {
		if ((((TeleportTile*)(mapController->positionToObject(beforeMovingPosition)))->trigger(this->direction, this))) {
			beforeMovingPosition = this->getPosition();
			passedPosition = beforeMovingPosition;
			isMoving = false;
			return;
		};
	}

	if (!isMoving) {
		passedPosition = beforeMovingPosition;
		beforeMovingPosition = this->getPosition();
		destination = getNearestPoint();
		isMoving = true;
	}
	else {
		Vec2 dir = (destination - beforeMovingPosition).getNormalized();
		this->direction = offsetToDirection(dir);
		Vec2 offset = dir * speed * deltaTime;
		Vec2 oldPosition = getPosition();
		Vec2 newPosition = oldPosition + offset;
		
		float x = oldPosition.distance(newPosition);
		float y = oldPosition.distance(destination);
		if (x < y) {
			this->setPosition(newPosition);
		}
		else {
			this->setPosition(destination);
			this->isMoving = false;
		}
	}
}

Vec2 Ghost::getNearestPoint()
{
	return mapController->getNearestPositionIgnore(beforeMovingPosition, passedPosition);
}

void Ghost::update(float deltaTime)
{
	move(deltaTime);
}

Ghost::Ghost()
{
}


Ghost::~Ghost()
{
}
