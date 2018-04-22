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

void Ghost::onEatenFormAction(float deltaTime)
{
	if (elapsedTime > 0) {
		elapsedTime -= deltaTime;
	}
	else {
		changeForm(GhostForm::Bad);
	}
}

void Ghost::doNothing()
{
}

bool Ghost::initialize(Sprite * sprite, std::string labelText, MapController * mapController)
{
	MovableObject::initialize(sprite, labelText, mapController);
	// Bad form
	animateList.pushBack(getAnimate({ " (27).png", " (28).png" }, 0.1f)); // RIGHT
	animateList.pushBack(getAnimate({ " (29).png", " (30).png" }, 0.1f)); // DOWN
	animateList.pushBack(getAnimate({ " (31).png", " (32).png" }, 0.1f)); // LEFT
	animateList.pushBack(getAnimate({ " (33).png", " (34).png" }, 0.1f)); // UP

	// Good form
	animateList.pushBack(getAnimate({ " (11).png", " (12).png" }, 0.1f)); // NEWLY
	animateList.pushBack(getAnimate({ " (11).png", " (12).png", " (13).png", " (14).png" }, 0.1f));  // ALMOST OVER

	// Eaten form
	animateList.pushBack(getAnimate({ " (78).png", " (79).png" }, 0.1f)); // RIGHT
	animateList.pushBack(getAnimate({ " (80).png", " (81).png" }, 0.1f)); // DOWN
	animateList.pushBack(getAnimate({ " (82).png", " (83).png" }, 0.1f)); // LEFT
	animateList.pushBack(getAnimate({ " (84).png", " (85).png" }, 0.1f)); // UP
	return true;
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
		confirmDirection();
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
		this->checkCollisionCallback = [=]() { onCheckCollision(); };
		this->formActionCallback = [=](float t) { doNothing(); };
		break;

	case GhostForm::Good:
		this->elapsedTime = this->goodFormTime;
		this->checkCollisionCallback = [=]() { onCheckCollision(); };
		this->formActionCallback = [=](float t) { onEatenFormAction(t); };
		break;

	default:
		this->checkCollisionCallback = [=]() { doNothing(); };
		this->formActionCallback = [=](float t) { doNothing(); };
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

void Ghost::confirmDirection()
{
	switch (form) {
	case GhostForm::Bad:
		switch (direction) {
		case Direction::Right: setAnimate(animateList.at(0)); break;
		case Direction::Down: setAnimate(animateList.at(1)); break;
		case Direction::Left: setAnimate(animateList.at(2)); break;
		case Direction::Up: setAnimate(animateList.at(3)); break;
		}
		break;
	case GhostForm::Good:
		setAnimate(animateList.at(4));
		break;
	case GhostForm::Eaten:
		switch (direction) {
		case Direction::Right: setAnimate(animateList.at(6)); break;
		case Direction::Down: setAnimate(animateList.at(7)); break;
		case Direction::Left: setAnimate(animateList.at(8)); break;
		case Direction::Up: setAnimate(animateList.at(9)); break;
		}
		break;
	}
	
}

void Ghost::update(float deltaTime)
{
	move(deltaTime);
	checkCollisionCallback();
	formActionCallback(deltaTime);
} 

Ghost::Ghost()
{
	this->target = nullptr;
	changeForm(GhostForm::Bad);
}

Ghost::~Ghost()
{
}
