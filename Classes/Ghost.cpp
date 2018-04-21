#include "Ghost.h"
#include "MapController.h"

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
	if (target == nullptr || !isReady()) {
		return;
	}

	if (mapController->positionToChar(beforeMovingPosition) == 'T' &&
		mapController->positionToObject(beforeMovingPosition)->triggerTile(this, this->direction)) {
		passedPosition = beforeMovingPosition;
		isMoving = false;
	}

	if (!isMoving) {
		if (!isChanging) {
			passedPosition = beforeMovingPosition;
			beforeMovingPosition = this->getPosition();
		}
		else {
			beforeMovingPosition = this->getPosition();
			passedPosition = beforeMovingPosition;
		}
		destination = getDestination();
		isMoving = true;
		isChanging = false;
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

Vec2 Ghost::getFurthestPoint() {
	return mapController->getFurthestPositionIgnore(beforeMovingPosition, passedPosition);
}

void Ghost::changeForm(GhostForm form)
{
	this->form = form;
	this->isChanging = true;
}

Vec2 Ghost::getDestination()
{
	switch (form) {
	case GhostForm::Bad:
		return getNearestPoint();
		
	case GhostForm::Good:
		return getFurthestPoint();

	case GhostForm::Eaten:
		break;
	}
}

void Ghost::update(float deltaTime)
{
	move(deltaTime);
} 

Ghost::Ghost()
{
	this->form = GhostForm::Bad;
}

Ghost::~Ghost()
{
}
