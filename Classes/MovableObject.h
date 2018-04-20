#pragma once

#include "cocos2d.h"
#include "StaticObject.h"
USING_NS_CC;

class MovableObject : public StaticObject
{
public:
	enum class Direction { Up = 0, Down = 1, Left = 2, Right = 3 };

public:
	float speed = 25;
	Vec2 beforeMovingPosition;

public:
	CREATE_FUNC(MovableObject);
	virtual bool init();
	virtual void move(float deltaTime);
	virtual void setSpeed(float speed);
	virtual void update(float deltaTime) override;

	virtual Vec2 directionToOffset(Direction direction);
	virtual Direction offsetToDirection(Vec2 offset);

public:
	MovableObject();
	~MovableObject();
};

