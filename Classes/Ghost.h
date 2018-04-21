#pragma once
#include "StaticObject.h"
#include "MovableObject.h"
#include "cocos2d.h"

class MapController;

class Ghost : public MovableObject
{
protected:
	Vec2 destination;
	Vec2 passedPosition;
	bool isMoving = false;
	bool isChanging = false;
	GhostForm form;

public: 
	Direction direction;
	StaticObject* target;
public:
	CREATE_FUNC(Ghost);
	virtual void setTarget(StaticObject* target);
	virtual void setMapController(MapController* mapController);
	virtual void move(float deltaTime);
	virtual Vec2 getNearestPoint();
	virtual Vec2 getFurthestPoint();
	virtual void changeForm(GhostForm form);
	virtual Vec2 getDestination();
	void update(float deltaTime) override;
	
	Ghost();
	~Ghost();
};

