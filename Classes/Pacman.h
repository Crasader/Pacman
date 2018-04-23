#pragma once
#include "cocos2d.h"
#include "MovableObject.h"

USING_NS_CC;

class MapController; // forward derclaration

class Pacman : public MovableObject
{
private:
	bool isAlive = true;

protected:
	Direction direction;
	Direction nextDirection;

public:
	virtual void setMap(MapController* mapController);
	virtual void setDirection(Direction direction);
	virtual void confirmDirection();
	virtual void move(float deltaTime);
	virtual void die();
	virtual void respawn();
	virtual bool initialize(cocos2d::Sprite * sprite, std::string labelText, MapController* mapController);

public:
	CREATE_FUNC(Pacman);
	void update(float deltaTime) override;
	
public:
	Pacman();
	~Pacman();
};


