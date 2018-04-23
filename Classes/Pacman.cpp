#include "Pacman.h"
#include "MapController.h"


void Pacman::setMap(MapController* mapController)
{
	this->mapController = mapController;
}

void Pacman::setDirection(Direction direction)
{
	this->nextDirection = direction;
}

void Pacman::confirmDirection()
{
	this->direction = this->nextDirection;
	switch (direction) {
	case Direction::Up: setAnimate(animateList.at(0)); break;
	case Direction::Down: setAnimate(animateList.at(1)); break;
	case Direction::Left: setAnimate(animateList.at(2)); break;
	case Direction::Right: setAnimate(animateList.at(3)); break;
	}
}

void Pacman::move(float deltaTime)
{
	if (!isAlive || !isReady()) { return; }

	auto destination = this->beforeMovingPosition + this->directionToOffset(this->direction) * mapController->blockSize;
	if (mapController->isWalkable(destination)) {
		Vec2 offset = directionToOffset(direction) * speed * deltaTime;
		Vec2 oldPosition = getPosition();
		Vec2 newPosition = oldPosition + offset;

		float x = oldPosition.distance(newPosition);
		float y = oldPosition.distance(destination);
		if (x < y) {
			this->setPosition(newPosition);
		}
		else {
			this->setPosition(destination);
			this->beforeMovingPosition = this->getPosition();
			auto newDestination = destination + this->directionToOffset(this->nextDirection) * mapController->blockSize;
			if (mapController->isWalkable(newDestination)) {
				confirmDirection();
			}
			mapController->positionToObject(beforeMovingPosition)->triggerTile(this, this->direction);
		}
	}
	else if (this->direction != this->nextDirection) {
		confirmDirection();
		move(deltaTime);
	}
}

void Pacman::die()
{
	isAlive = false;
	this->setAnimate(animateList.at(4), [=]() {
		mapController->respawn();
	});
}

void Pacman::respawn() {
	this->setPosition(mapController->playerSpawn->getPosition());
	this->beforeMovingPosition = this->getPosition();
	this->setDirection(Direction::Right);
	this->setAnimate(animateList.at(3));
	isAlive = true;
}

bool Pacman::initialize(cocos2d::Sprite * sprite, std::string labelText, MapController* mapController)
{
	EventListenerKeyboard* keyboardListener = EventListenerKeyboard::create();
	keyboardListener->onKeyPressed = [=](EventKeyboard::KeyCode keyCode, Event* event) {
		if (keyCode == EventKeyboard::KeyCode::KEY_UP_ARROW) {
			this->setDirection(Direction::Up);
		}
		else if (keyCode == EventKeyboard::KeyCode::KEY_DOWN_ARROW) {
			this->setDirection(Direction::Down);
		}
		else if (keyCode == EventKeyboard::KeyCode::KEY_LEFT_ARROW) {
			this->setDirection(Direction::Left);
		}
		else if (keyCode == EventKeyboard::KeyCode::KEY_RIGHT_ARROW) {
			this->setDirection(Direction::Right);
		} 
		else if (keyCode == EventKeyboard::KeyCode::KEY_1) {
			mapController->changeGhostForm(GhostForm::Good);
		}
		else if (keyCode == EventKeyboard::KeyCode::KEY_2) {
			mapController->changeGhostForm(GhostForm::Bad);
		}
		else if (keyCode == EventKeyboard::KeyCode::KEY_3) {
			mapController->changeGhostForm(GhostForm::Eaten);
		}
	};
	this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(keyboardListener, this);
	this->direction = this->nextDirection = Direction::Right;

	MovableObject::initialize(sprite, labelText, mapController);
	animateList.pushBack(getAnimate({ " (2).png", " (4).png", " (39).png" }, 0.1f)); // Up
	animateList.pushBack(getAnimate({ " (6).png", " (8).png", " (39).png" }, 0.1f)); // Down
	animateList.pushBack(getAnimate({ " (1).png", " (3).png", " (39).png" }, 0.1f)); // Left
	animateList.pushBack(getAnimate({ " (5).png", " (7).png", " (39).png" }, 0.1f)); // Right
	animateList.pushBack(getAnimate({ " (43).png", " (44).png", " (45).png", " (46).png", " (47).png", " (48).png",
		" (49).png", " (50).png", " (51).png", " (52).png", " (53).png" }, 0.05f)); // Death
	setAnimate(animateList.at(3));
	return true;
}

void Pacman::update(float deltaTime)
{
	move(deltaTime);
}

Pacman::Pacman()
{
}

Pacman::~Pacman()
{
}
