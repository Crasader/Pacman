#include "Ghost.h"
#include "MapController.h"


void Ghost::onGoodFormCollision()
{
	if (target == nullptr || !isReady()) {
		return;
	}
	auto player = mapController->player;
	float distance = player->getPosition().distance(this->getPosition());
	if (distance > mapController->blockSize) {
		return;
	}
	auto pBox = player->sprite->getBoundingBox();
	auto gBox = this->sprite->getBoundingBox();
	if (pBox.intersectsRect(gBox)) {
		changeForm(GhostForm::Eaten);
		confirmDirection();
		mapController->wait(1.0f);
	}
}

void Ghost::onBadFormCollision()
{
	if (target == nullptr || !isReady()) {
		return;
	}
	auto player = mapController->player;
	float distance = player->getPosition().distance(this->getPosition());
	if (distance > mapController->blockSize) {
		return;
	}
	auto pBox = player->sprite->getBoundingBox();
	auto gBox = this->sprite->getBoundingBox();
	if (pBox.intersectsRect(gBox)) {
		player->die();
	}
}

void Ghost::onEatenFormAction(float deltaTime)
{
	if (elapsedTime > 0) {
		elapsedTime -= deltaTime;
	}
	else {
		changeForm(previousForm);
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

void Ghost::setRadius(float radius)
{
	this->radius = radius;
}

void Ghost::setDefaultRadius(float radius)
{
	this->defaultRadius = radius;
}

void Ghost::setGhostColor(int index)
{
	index = (index > 3 || index < 0) ? 0 : index;
	this->stopAllActions();
	if (index == 0) {
		animateList.replace(0, getAnimate({ " (27).png", " (28).png" }, 0.1f)); // RIGHT
		animateList.replace(1, getAnimate({ " (29).png", " (30).png" }, 0.1f)); // DOWN
		animateList.replace(2, getAnimate({ " (31).png", " (32).png" }, 0.1f)); // LEFT
		animateList.replace(3, getAnimate({ " (33).png", " (34).png" }, 0.1f)); // UP
	}
	else if (index == 1) {
		animateList.replace(0, getAnimate({ " (54).png", " (55).png" }, 0.1f)); // RIGHT
		animateList.replace(1, getAnimate({ " (56).png", " (57).png" }, 0.1f)); // DOWN
		animateList.replace(2, getAnimate({ " (58).png", " (59).png" }, 0.1f)); // LEFT
		animateList.replace(3, getAnimate({ " (60).png", " (61).png" }, 0.1f)); // UP
	}
	else if (index == 2) {
		animateList.replace(0, getAnimate({ " (62).png", " (63).png" }, 0.1f)); // RIGHT
		animateList.replace(1, getAnimate({ " (64).png", " (65).png" }, 0.1f)); // DOWN
		animateList.replace(2, getAnimate({ " (66).png", " (67).png" }, 0.1f)); // LEFT
		animateList.replace(3, getAnimate({ " (68).png", " (69).png" }, 0.1f)); // UP
	}
	else {
		animateList.replace(0, getAnimate({ " (70).png", " (71).png" }, 0.1f)); // RIGHT
		animateList.replace(1, getAnimate({ " (72).png", " (73).png" }, 0.1f)); // DOWN
		animateList.replace(2, getAnimate({ " (74).png", " (75).png" }, 0.1f)); // LEFT
		animateList.replace(3, getAnimate({ " (76).png", " (77).png" }, 0.1f)); // UP
	}
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
		destination = getDestinationCallback();
		isMoving = true;
		isChanging = false;
	}
	else {
		Vec2 dir = (destination - beforeMovingPosition).getNormalized();
		this->direction = offsetToDirection(dir);
		Vec2 offset = dir * getSpeedCallback() * deltaTime;
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

void Ghost::respawn()
{
	this->setPosition(mapController->enemySpawn->getPosition());
	this->beforeMovingPosition = this->getPosition();
	this->isMoving = false;
	this->changeForm(GhostForm::Base);
	this->confirmDirection();
}

Vec2 Ghost::getNearestPoint()
{
	if (radius > 0 && beforeMovingPosition.distance(target->getPosition()) > radius) {
		return getRandomPosition();
	}
	return mapController->getNearestPosition(beforeMovingPosition, target->getPosition(), passedPosition, form);
}

Vec2 Ghost::getFurthestPoint() {
	if (radius > 0 && beforeMovingPosition.distance(target->getPosition()) > radius) {
		return getRandomPosition();
	}
	return mapController->getFurthestPosition(beforeMovingPosition, target->getPosition(), passedPosition, form);
}

Vec2 Ghost::getRandomPosition()
{
	return mapController->getRandomPosition(beforeMovingPosition, passedPosition);
}

void Ghost::changeForm(GhostForm form, std::initializer_list<GhostForm> ignoreList)
{
	for each(GhostForm f in ignoreList) {
		if (this->form == f) {
			return;
		}
	}

	if (this->form != form) {
		this->previousForm = this->form;
	}
	this->form = form;
	this->isChanging = true;

	switch (this->form) {
	case GhostForm::Bad:
		setTarget(mapController->player);
		setRadius(defaultRadius);
		this->checkCollisionCallback = [=]() { onBadFormCollision(); };
		this->formActionCallback = [=](float t) { doNothing(); };
		this->getDestinationCallback = [=]() { return getNearestPoint(); };
		this->getSpeedCallback = [=]() { return speed; };
		break;

	case GhostForm::Good:
		setTarget(mapController->player);
		setRadius(defaultRadius);
		this->elapsedTime = this->goodFormTime;
		this->checkCollisionCallback = [=]() { onGoodFormCollision(); };
		this->formActionCallback = [=](float t) { onEatenFormAction(t); };
		this->getDestinationCallback = [=]() { return getFurthestPoint(); };
		this->getSpeedCallback = [=]() { return speed / 2; };
		break;

	case GhostForm::Eaten:
		setTarget(mapController->base);
		setRadius(-1);
		this->checkCollisionCallback = [=]() { doNothing(); };
		this->formActionCallback = [=](float t) { doNothing(); };
		this->getDestinationCallback = [=]() { return getNearestPoint(); };
		this->getSpeedCallback = [=]() { return speed * 2; };
		break;

	case GhostForm::Door:
		setTarget(mapController->door);
		setRadius(-1);
		this->checkCollisionCallback = [=]() { doNothing(); };
		this->formActionCallback = [=](float t) { doNothing(); };
		this->getDestinationCallback = [=]() { return getNearestPoint(); };
		this->getSpeedCallback = [=]() { return speed; };
		break;

	default:
		setTarget(mapController->player);
		setRadius(-1);
		this->checkCollisionCallback = [=]() { doNothing(); };
		this->formActionCallback = [=](float t) { doNothing(); };
		this->getDestinationCallback = [=]() { return getRandomPosition(); };
		this->getSpeedCallback = [=]() { return speed; };
		break;
	}
}

GhostForm Ghost::getForm()
{
	return this->form;
}

GhostForm Ghost::getPreviousForm()
{
	return this->previousForm;
}

void Ghost::confirmDirection()
{
	switch (form) {
	case GhostForm::Bad:
	case GhostForm::Door:
	case GhostForm::Base:
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
	this->radius = -1;
	this->defaultRadius = -1;
	this->direction = Direction::Right;
}

Ghost::~Ghost()
{
}
