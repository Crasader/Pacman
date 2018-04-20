#include "Pacman.h"
#include "MapController.h"
#include "TeleportTile.h"

void Pacman::setMap(MapController* mapController)
{
	this->mapController = mapController;
}

void Pacman::setDirection(Direction direction)
{
	this->nextDirection = direction;
}

void Pacman::move(float deltaTime)
{
	if (mapController->positionToChar(beforeMovingPosition) == 'T') {
		if ((((TeleportTile*)(mapController->positionToObject(beforeMovingPosition)))->trigger(this->direction, this))) {
			beforeMovingPosition = this->getPosition();
			return;
		};
	}

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
				this->direction = this->nextDirection;
			}
		}
	}
	else if (this->direction != this->nextDirection) {
		this->direction = this->nextDirection;
		move(deltaTime);
	}
}

bool Pacman::initialize(cocos2d::Sprite * sprite, std::string labelText)
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
	};
	this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(keyboardListener, this);
	this->direction = this->nextDirection = Direction::Right;
	return MovableObject::initialize(sprite, labelText);
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
