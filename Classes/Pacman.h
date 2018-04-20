#pragma once
#include "cocos2d.h"
#include "MovableObject.h"

USING_NS_CC;

class MapController; // forward derclaration

class Pacman : public MovableObject
{
protected:
	MapController* mapController;
	Direction direction;
	Direction nextDirection;
	
public:
	virtual void setMap(MapController* mapController);
	virtual void setDirection(Direction direction);
	virtual void move(float deltaTime);
	virtual bool initialize(cocos2d::Sprite * sprite, std::string labelText);

public:
	CREATE_FUNC(Pacman);
	void update(float deltaTime) override;
	
public:
	Pacman();
	~Pacman();
};


