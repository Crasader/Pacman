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
	GhostForm previousForm;

	float defaultRadius;
	float radius;

	std::function<void()> checkCollisionCallback;
	std::function<void(float)> formActionCallback;
	std::function<Vec2()> getDestinationCallback;
	std::function<float()> getSpeedCallback;

private:
	float goodFormTime = 5;
	float elapsedTime = 0;

protected:
	virtual void onGoodFormCollision();
	virtual void onBadFormCollision();
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
	virtual void setRadius(float radius);
	virtual void setDefaultRadius(float radius);

	virtual void setGhostColor(int index);

	virtual void setMapController(MapController* mapController);
	virtual void move(float deltaTime);
	virtual void respawn();

	virtual Vec2 getNearestPoint();
	virtual Vec2 getFurthestPoint();
	virtual Vec2 getRandomPosition();

	virtual void changeForm(GhostForm form, std::initializer_list<GhostForm> ignoreList = {});
	virtual GhostForm getForm();
	virtual GhostForm getPreviousForm();
	virtual void confirmDirection();

	void update(float deltaTime) override;
	
	Ghost();
	~Ghost();
};

