#include "MovableObject.h"



bool MovableObject::init()
{
	this->scheduleUpdate();
	return StaticObject::init();
}


void MovableObject::move(float deltaTime)
{

}


void MovableObject::setSpeed(float speed)
{
	this->speed = speed;
}


void MovableObject::update(float deltaTime)
{

}


Vec2 MovableObject::directionToOffset(Direction direction)
{
	Vec2 offset = Vec2::ZERO;
	if (direction == Direction::Up) {
		offset.y++;
	}
	else if (direction == Direction::Down) {
		offset.y--;
	}
	else if (direction == Direction::Left) {
		offset.x--;
	}
	else if (direction == Direction::Right) {
		offset.x++;
	}
	return offset;
}

MovableObject::Direction MovableObject::offsetToDirection(Vec2 offset)
{
	if (offset.x > 0) return Direction::Right;
	if (offset.x < 0) return Direction::Left;
	if (offset.y > 0) return Direction::Up;
	if (offset.y < 0) return Direction::Down;
	return Direction::Up;
}


MovableObject::MovableObject()
{
}


MovableObject::~MovableObject()
{
}
