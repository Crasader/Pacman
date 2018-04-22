#pragma once
#include "StaticObject.h"
#include "MovableObject.h"
#include "cocos2d.h"

class MapController;

class Ghost : public MovableObject
{
protected:
	Vec2 destination;
	bool isChanging = false;
	GhostForm form;
	std::function<void()> checkCollisionCallback;
	std::function<void(float)> formActionCallback;

private:
	float goodFormTime = 5;
	float elapsedTime = 0;

protected:
	virtual void onCheckCollision();
	virtual void onEatenFormAction(float deltaTime);
	virtual void doNothing();

public: 
	Direction direction;
	StaticObject* target;
	Vec2 passedPosition;
	bool isMoving = false;

public:
	CREATE_FUNC(Ghost);
	virtual bool initialize(Sprite* sprite, std::string labelText, MapController* mapController);
	virtual void setTarget(StaticObject* target);
	virtual void setMapController(MapController* mapController);
	virtual void move(float deltaTime);
	virtual Vec2 getNearestPoint();
	virtual Vec2 getFurthestPoint();
	virtual void changeForm(GhostForm form);
	virtual Vec2 getDestination();
	virtual GhostForm getForm();
	virtual float getSpeed();
	virtual void confirmDirection();

	void update(float deltaTime) override;
	
	Ghost();
	~Ghost();
};

