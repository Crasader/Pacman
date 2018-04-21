#include "Ghost.h"
#include "MapController.h"

void Ghost::onCheckCollision()
{
	if (target == nullptr || !isReady()) {
		return;
	}
	auto player = mapController->player;
	float distance = player->getPosition().distance(this->getPosition());
	if (distance > mapController->blockSize) {
		return;
	}
	auto pBox = player->getBoundingBox();
	auto gBox = this->getBoundingBox();
	if (player->getBoundingBox().intersectsRect(this->getBoundingBox())) {
		changeForm(GhostForm::Eaten);
	}
}

void Ghost::onNotCheckCollision()
{
}

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

	mapController->positionToObject(beforeMovingPosition)->triggerTile(this, this->direction);

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
		Vec2 offset = dir * getSpeed() * deltaTime;
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
	return mapController->getNearestPosition(beforeMovingPosition, target->getPosition(), passedPosition, form);
}

Vec2 Ghost::getFurthestPoint() {
	return mapController->getFurthestPosition(beforeMovingPosition, target->getPosition(), passedPosition, form);
}

void Ghost::changeForm(GhostForm form)
{
	this->form = form;
	this->isChanging = true;

	switch (this->form) {
	case GhostForm::Bad:
	case GhostForm::Good:
		this->checkCollisionCallback = std::bind(&Ghost::onCheckCollision, this);
		break;

	default:
		this->checkCollisionCallback = std::bind(&Ghost::onNotCheckCollision, this);
	}
}

Vec2 Ghost::getDestination()
{
	switch (form) {
	case GhostForm::Bad:
		return getNearestPoint();
		
	case GhostForm::Good:
		return getFurthestPoint();

	case GhostForm::Eaten:
		this->setTarget(mapController->base);
		return getNearestPoint();
	}
}

GhostForm Ghost::getForm()
{
	return this->form;
}

float Ghost::getSpeed()
{
	switch (form) {
	case GhostForm::Bad:
		return speed;

	case GhostForm::Good:
		return speed / 2;

	case GhostForm::Eaten:
		this->setTarget(mapController->base);
		return speed * 2;
	}
}

void Ghost::update(float deltaTime)
{
	move(deltaTime);
	checkCollisionCallback();
} 

Ghost::Ghost()
{
	this->form = GhostForm::Bad;
	this->target = nullptr;
	this->checkCollisionCallback = std::bind(&Ghost::onCheckCollision, this);
}

Ghost::~Ghost()
{
}
